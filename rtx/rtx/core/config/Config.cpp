/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Config.cpp
*/

#include "Config.hpp"

#include <rtx/core/scene/Camera.hpp>
#include <rtx/maths/Point.hpp>

#include <algorithm>
#include <iostream>
#include <libconfig.h++>

#include "Factory.hpp"

namespace {
constexpr double degres_to_radian(double degres) {
    return degres / 180 * std::numbers::pi;
}
}  // namespace

namespace rtx::config {

Config::Config() = default;

Config::Config(const std::string &path) {
    readFile(path);
}

void Config::readFile(const std::string &path) {
    std::clog << "Config:\tLoading config in \"" << path << "\"...\n";
    _config.readFile(path);
}

libconfig::Setting &Config::lookup(const std::string &name) const {
    return lookup(name, _config.getRoot());
}

libconfig::Setting &Config::lookup(const std::string &name, const libconfig::Setting &setting) {
    if (!setting.exists(name)) {
        throw std::runtime_error(
            "Config: No " + std::string(setting.getName()) + "." + name + " found in config file"
        );
    }
    return setting.lookup(name);
}

render::Color Config::parseColor(const libconfig::Setting &obj) {
    return {
        std::clamp<int>(lookup("r", obj), 0, 255) / 255.,
        std::clamp<int>(lookup("g", obj), 0, 255) / 255.,
        std::clamp<int>(lookup("b", obj), 0, 255) / 255.,
    };
}

render::Materials Config::parseMaterial(const libconfig::Setting &obj) {
    return render::Materials{parseColor(Config::lookup("diffuse", obj))};
}

scene::Camera Config::parseCamera() const {
    const auto &cam = lookup("camera");

    return {
        parsePoint<double>(lookup("position", cam)),
        {degres_to_radian(lookup("angle.x", cam)),
         degres_to_radian(lookup("angle.y", cam)),
         degres_to_radian(lookup("angle.z", cam))},
        {static_cast<size_t>(int(lookup("resolution.width", cam))),  // This lib sucks, I
         static_cast<size_t>(int(lookup("resolution.height", cam)))
        },  // can't convert directly, even
        degres_to_radian(lookup("fov", cam))
    };  // through it is in the doc...
}

scene::RenderConfig Config::parseRenderConfig(const libconfig::Setting &obj) {
    using namespace scene::settings;
    std::string mode = lookup_or_else("render_mode", obj, "fast");
    if (mode == "fast") {
        const std::string aa = lookup_or_else("antialiasing", obj, "none");
        if (aa == "none") {
            return FastRenderConfig{Antialiasing::NONE};
        }
        if (aa == "msaa_x4") {
            return FastRenderConfig{Antialiasing::MSAA_X4};
        }
        throw std::runtime_error("Config: Unknown antialiasing mode: " + aa);
    }
    if (mode == "path_tracing") {
        return PathTracerRenderConfig{
            static_cast<unsigned int>(std::max(lookup_or_else("samples", obj, 10), 0)),
            static_cast<unsigned int>(std::max(lookup_or_else("max_bounces", obj, 5), 0))
        };
    }
    throw std::runtime_error("Config: Unknown render mode: " + mode);
}

scene::Scene Config::parseScene() const {
    const auto &cfg = lookup("scene");
    scene::Scene scene{parseRenderConfig(cfg)};

    for (const auto &obj : lookup("objects", cfg)) {
        scene.addObject(ConfigFactory::getObj(lookup("type", obj), obj));
    }
    for (const auto &light : lookup("lights", cfg)) {
        scene.addLight(ConfigFactory::getLight(light));
    }
    scene.setAmbientLight(ConfigFactory::parseAmbientLight(lookup("ambient_light", cfg)));
    return scene;
}
}  // namespace rtx::config
