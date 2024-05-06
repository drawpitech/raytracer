/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Config.hpp
*/

#pragma once

#include <libconfig.h++>
#include <string>

namespace rtx::core {

class Config {
   public:
    Config();

    Config(const std::string &path);
    void readFile(const std::string &path);

   private:
    libconfig::Config _config;
};

}  // namespace rtx::core
