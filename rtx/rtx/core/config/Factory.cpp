/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Factory.cpp
*/

#include "Factory.hpp"

#include <rtx/core/shapes/Cone.hpp>
#include <rtx/core/shapes/Cylinder.hpp>
#include <rtx/core/shapes/InfiniteCylinder.hpp>
#include <rtx/core/shapes/Plane.hpp>
#include <rtx/core/shapes/Sphere.hpp>

#include <algorithm>
#include <functional>
#include <libconfig.h++>
#include <map>
#include <memory>
#include <string>

#include "Config.hpp"

namespace rtx::config {

std::unique_ptr<rtx::shapes::AObject>
ConfigFactory::getObj(const std::string &type, const libconfig::Setting &obj) {
    if (!OBJECTS_MAP.contains(type)) {
        throw std::runtime_error("Unknown object type: " + type);
    }
    return OBJECTS_MAP.at(type)(obj);
}

template <>
std::unique_ptr<rtx::shapes::AObject> ConfigFactory::getObj<shapes::Sphere>(
    const libconfig::Setting &obj
) {
    return std::make_unique<shapes::Sphere>(
        Config::parsePoint<double>(Config::lookup("position", obj)),
        Config::lookup("radius", obj),
        Config::parseMaterial(Config::lookup("material", obj))
    );
}

template <>
std::unique_ptr<rtx::shapes::AObject> ConfigFactory::getObj<rtx::shapes::Plane>(
    const libconfig::Setting &obj
) {
    return std::make_unique<shapes::Plane>(
        Config::parseVector<double>(Config::lookup("normal", obj)),
        Config::parsePoint<double>(Config::lookup("position", obj)),
        Config::parseMaterial(Config::lookup("material", obj))
    );
}

template <>
std::unique_ptr<rtx::shapes::AObject> ConfigFactory::getObj<rtx::shapes::Cylinder>(
    const libconfig::Setting &obj
) {
    return std::make_unique<shapes::Cylinder>(
        Config::parseVector<double>(Config::lookup("axis", obj)),
        Config::parsePoint<double>(Config::lookup("position", obj)),
        Config::lookup("radius", obj),
        Config::lookup("height", obj),
        Config::parseMaterial(Config::lookup("material", obj))
    );
}

template <>
std::unique_ptr<rtx::shapes::AObject> ConfigFactory::getObj<rtx::shapes::Disk>(
    const libconfig::Setting &obj
) {
    return std::make_unique<shapes::Disk>(
        Config::parseVector<double>(Config::lookup("axis", obj)),
        Config::parsePoint<double>(Config::lookup("position", obj)),
        Config::lookup("radius", obj),
        Config::parseMaterial(Config::lookup("material", obj))
    );
}

template <>
std::unique_ptr<rtx::shapes::AObject> ConfigFactory::getObj<rtx::shapes::InfiniteCylinder>(
    const libconfig::Setting &obj
) {
    return std::make_unique<shapes::InfiniteCylinder>(
        Config::parseVector<double>(Config::lookup("axis", obj)),
        Config::parsePoint<double>(Config::lookup("position", obj)),
        Config::lookup("radius", obj),
        Config::parseMaterial(Config::lookup("material", obj))
    );
}

template <>
std::unique_ptr<rtx::shapes::AObject> ConfigFactory::getObj<rtx::shapes::Cone>(
    const libconfig::Setting &obj
) {
    return std::make_unique<shapes::Cone>(
        Config::parseVector<double>(Config::lookup("axis", obj)),
        Config::parsePoint<double>(Config::lookup("position", obj)),
        Config::lookup("radius", obj),
        Config::parseMaterial(Config::lookup("material", obj))
    );
}

std::unique_ptr<render::DirectionalLight> ConfigFactory::getLight(const libconfig::Setting &obj) {
    return std::make_unique<render::DirectionalLight>(
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

const std::map<
    std::string,
    std::function<std::unique_ptr<rtx::shapes::AObject>(const libconfig::Setting &)>>
    ConfigFactory::OBJECTS_MAP = {
        {"sphere", ConfigFactory::getObj<rtx::shapes::Sphere>},
        {"plane", ConfigFactory::getObj<rtx::shapes::Plane>},
        {"cylinder", ConfigFactory::getObj<rtx::shapes::Cylinder>},
        {"infinite_cylinder", ConfigFactory::getObj<rtx::shapes::InfiniteCylinder>},
        {"disk", ConfigFactory::getObj<rtx::shapes::Disk>},
        {"cone", ConfigFactory::getObj<rtx::shapes::Cone>},
};

}  // namespace rtx::config
