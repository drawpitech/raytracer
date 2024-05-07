/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Factory.hpp
*/

#pragma once

#include <functional>
#include <libconfig.h++>
#include <map>
#include <memory>
#include <rtx/render/Primitives/Sphere.hpp>
#include <string>

namespace rtx::core {
class ConfigFactory {
   public:
    static std::unique_ptr<Object> get(
        const std::string &type, const libconfig::Setting &);

   private:
    template <typename T>
    static std::unique_ptr<Object> get(const libconfig::Setting &);

    static const std::map<
        std::string,
        std::function<std::unique_ptr<Object>(const libconfig::Setting &)>>
        FACTORY_MAP;
};
}  // namespace rtx::core
