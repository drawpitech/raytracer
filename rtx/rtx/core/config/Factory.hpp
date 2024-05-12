/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Factory.hpp
*/

#pragma once

#include <rtx/core/render/AmbientLight.hpp>
#include <rtx/core/render/DirectionalLights.hpp>
#include <rtx/core/shapes/AObject.hpp>

#include <functional>
#include <libconfig.h++>
#include <map>
#include <memory>
#include <string>

namespace rtx::config {
class ConfigFactory {
   public:
    static std::unique_ptr<rtx::shapes::AObject>
    getObj(const std::string &type, const libconfig::Setting &obj);
    static std::unique_ptr<render::DirectionalLight> getLight(const libconfig::Setting &obj);
    static render::AmbientLight parseAmbientLight(const libconfig::Setting &obj);

   private:
    template <typename T>
    static std::unique_ptr<rtx::shapes::AObject> getObj(const libconfig::Setting &obj);

    static const std::map<
        std::string,
        std::function<std::unique_ptr<rtx::shapes::AObject>(const libconfig::Setting &)>>
        OBJECTS_MAP;
};
}  // namespace rtx::config
