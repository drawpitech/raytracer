/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Config.hpp
*/

#pragma once

#include <libconfig.h++>
#include <rtx/core/Scene.hpp>
#include <rtx/render/Camera.hpp>
#include <string>

namespace rtx::core {

class Config {
   public:
    Config();

    Config(const std::string &path);
    void readFile(const std::string &path);

    libconfig::Setting &lookup(const std::string &name);
    static libconfig::Setting &lookup(
        const std::string &name, const libconfig::Setting &setting);

    basics::Camera parseCamera();
    core::Scene parseScene();

   private:
    libconfig::Config _config;
};

}  // namespace rtx::core
