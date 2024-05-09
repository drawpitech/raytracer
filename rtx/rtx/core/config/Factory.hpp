/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Factory.hpp
*/

#pragma once

#include <rtx/core/render/Sphere.hpp>

#include <functional>
#include <libconfig.h++>
#include <map>
#include <memory>
#include <string>

namespace rtx::config {
class ConfigFactory {
   public:
    static std::unique_ptr<render::IObject>
    getObj(const std::string &type, const libconfig::Setting &obj);
    static std::unique_ptr<render::DirectionalLights> getLight(const libconfig::Setting &obj);
    static render::AmbientLight parseAmbientLight(const libconfig::Setting &obj);

   private:
    template <typename T>
    static std::unique_ptr<render::IObject> getObj(const libconfig::Setting &obj);

    static const std::map<
        std::string,
        std::function<std::unique_ptr<render::IObject>(const libconfig::Setting &)>>
        OBJECTS_MAP;
};
}  // namespace rtx::config
