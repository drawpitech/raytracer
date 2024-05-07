/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Config.cpp
*/

#include "Config.hpp"
#include "Factory.hpp"

#include <iostream>
#include <libconfig.h++>
#include <rtx/render/Camera.hpp>
#include <rtx/render/Primitives/Sphere.hpp>
#include <rtx/maths/Point.hpp>

namespace {
constexpr double degres_to_radian(double degres) {
    return degres / 180 * std::numbers::pi;
}
}  // namespace

namespace rtx::core {
Config::Config() = default;

Config::Config(const std::string &path) {
    readFile(path);
}

void Config::readFile(const std::string &path) {
    std::clog << "Config:\tLoading config in \"" << path << "\"...\n";
    _config.readFile(path);
}

libconfig::Setting &Config::lookup(const std::string &name) {
    return lookup(name, _config.getRoot());
}

libconfig::Setting &Config::lookup(
    const std::string &name, const libconfig::Setting &setting) {
    if (!setting.exists(name))
        throw std::runtime_error(
            "Config: No " + std::string(setting.getName()) + "." + name +
            " found in config file");
    return setting.lookup(name);
}

rtx::basics::Camera Config::parseCamera() {
    auto &cam = lookup("camera");

    return {
        {lookup("position.x", cam), lookup("position.y", cam),
         lookup("position.z", cam)},
        {degres_to_radian(lookup("angle.x", cam)),
         degres_to_radian(lookup("angle.y", cam)),
         degres_to_radian(lookup("angle.z", cam))},
        {size_t(int(lookup("resolution.width", cam))),  // This lib sucks, I
         size_t(int(lookup(
             "resolution.height", cam)))},      // can't convert directly, even
        degres_to_radian(lookup("fov", cam))};  // through it is in the doc...
}

Scene Config::parseScene() {
    auto &scene_cfg = lookup("scene");
    auto &objs = lookup("objects", scene_cfg);

    Scene scene;
    for (const auto &obj : objs)
        scene.addObject(ConfigFactory::get(obj["type"], obj));
    return scene;
}
}  // namespace rtx::core
