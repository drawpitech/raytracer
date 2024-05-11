/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Factory.cpp
*/

#include "Factory.hpp"

#include <rtx/core/render/Plane.hpp>
#include <rtx/core/render/Sphere.hpp>

#include <algorithm>
#include <functional>
#include <libconfig.h++>
#include <map>
#include <memory>
#include <string>

#include "Config.hpp"

namespace rtx::config {

std::unique_ptr<render::IObject>
ConfigFactory::getObj(const std::string &type, const libconfig::Setting &obj) {
    if (!OBJECTS_MAP.contains(type)) {
        throw std::runtime_error("Unknown object type: " + type);
    }
    return OBJECTS_MAP.at(type)(obj);
}

template <>
std::unique_ptr<render::IObject> ConfigFactory::getObj<render::Sphere>(const libconfig::Setting &obj
) {
    return std::make_unique<render::Sphere>(
        Config::parsePoint<double>(Config::lookup("position", obj)),
        Config::lookup("radius", obj),
        Config::parseMaterial(Config::lookup("material", obj))
    );
}

template <>
std::unique_ptr<render::IObject> ConfigFactory::getObj<render::Plane>(const libconfig::Setting &obj
) {
    return std::make_unique<render::Plane>(
        Config::parseVector<double>(Config::lookup("normal", obj)),
        Config::parsePoint<double>(Config::lookup("position", obj)),
        Config::parseMaterial(Config::lookup("material", obj))
    );
}

std::unique_ptr<render::DirectionalLights> ConfigFactory::getLight(const libconfig::Setting &obj) {
    return std::make_unique<render::DirectionalLights>(
        Config::parseVector<double>(Config::lookup("direction", obj)),
        std::clamp<float>(Config::lookup("intensity", obj), 0, 1),
        Config::parseColor(Config::lookup("color", obj))
    );
}

render::AmbientLight ConfigFactory::parseAmbientLight(const libconfig::Setting &obj) {
    return {
        Config::parseColor(Config::lookup("color", obj)),
        std::clamp<float>(Config::lookup("intensity", obj), 0, 1)
    };
}

const std::
    map<std::string, std::function<std::unique_ptr<render::IObject>(const libconfig::Setting &)>>
        ConfigFactory::OBJECTS_MAP = {
            {"sphere", ConfigFactory::getObj<rtx::render::Sphere>},
            {"plane", ConfigFactory::getObj<rtx::render::Plane>},
};

}  // namespace rtx::config
