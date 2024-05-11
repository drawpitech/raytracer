/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Config.cpp
*/

#include "Config.hpp"

#include <rtx/core/others/Camera.hpp>
#include <rtx/maths/Point.hpp>

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

others::Camera Config::parseCamera() {
    auto &cam = lookup("camera");

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

others::RenderConfig::RenderMode Config::parseRenderMode(const libconfig::Setting &obj) {
    std::string mode = lookup_or_else("render_mode", obj, "fast");
    if (mode == "fast") {
        return others::RenderConfig::RenderMode::FAST;
    }
    if (mode == "path_tracing") {
        return others::RenderConfig::RenderMode::PATH_TRACER;
    }
    throw std::runtime_error("Unknown render mode: " + mode);
}

others::Scene Config::parseScene() {
    const auto &cfg = lookup("scene");
    others::Scene scene{{
        static_cast<unsigned int>(std::max(lookup_or_else("samples", cfg, 10), 0)),
        static_cast<unsigned int>(std::max(lookup_or_else("max_bounces", cfg, 5), 0)),
        parseRenderMode(cfg)
    }};

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
