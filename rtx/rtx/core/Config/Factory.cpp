/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Factory.cpp
*/

#include "Factory.hpp"

#include <functional>
#include <libconfig.h++>
#include <map>
#include <memory>
#include <rtx/render/Primitives/Sphere.hpp>
#include <string>

#include "Config.hpp"

namespace rtx::core {

std::unique_ptr<Object> ConfigFactory::get(
    const std::string &type, const libconfig::Setting &obj) {
    if (FACTORY_MAP.find(type) == FACTORY_MAP.end())
        throw std::runtime_error("Unknown object type: " + type);
    return FACTORY_MAP.at(type)(obj);
}

template <>
std::unique_ptr<Object> ConfigFactory::get<rtx::basics::Sphere>(
    const libconfig::Setting &obj) {

    return std::make_unique<rtx::basics::Sphere>(
        rtx::maths::Point3<double>{
            Config::lookup("x", obj), Config::lookup("y", obj),
            Config::lookup("z", obj)},
        Config::lookup("radius", obj));
}

const std::map<
    std::string,
    std::function<std::unique_ptr<Object>(const libconfig::Setting &)>>
    ConfigFactory::FACTORY_MAP = {
        {"sphere", ConfigFactory::get<rtx::basics::Sphere>},
};

}  // namespace rtx::core
