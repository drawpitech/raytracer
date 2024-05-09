/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Config.hpp
*/

#pragma once

#include <rtx/core/others/Camera.hpp>
#include <rtx/core/others/Scene.hpp>

#include <libconfig.h++>
#include <string>

namespace rtx::config {

class Config {
   public:
    Config();

    explicit Config(const std::string &path);
    void readFile(const std::string &path);

    [[nodiscard]] libconfig::Setting &lookup(const std::string &name) const;
    static libconfig::Setting &lookup(const std::string &name, const libconfig::Setting &setting);

    template <typename T>
    static maths::Point3<T> parsePoint(const libconfig::Setting &obj) {
        return {lookup("x", obj), lookup("y", obj), lookup("z", obj)};
    }

    template <typename T>
    static maths::Vector3<T> parseVector(const libconfig::Setting &obj) {
        return {lookup("x", obj), lookup("y", obj), lookup("z", obj)};
    }

    static render::Color parseColor(const libconfig::Setting &obj);
    static render::Materials parseMaterial(const libconfig::Setting &obj);
    others::Camera parseCamera();
    static others::RenderConfig::RenderMode parseRenderMode(const libconfig::Setting &obj);
    others::Scene parseScene();

   private:
    libconfig::Config _config;
};

}  // namespace rtx::config
