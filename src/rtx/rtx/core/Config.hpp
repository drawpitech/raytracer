/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Config.hpp
*/

#pragma once

#include <libconfig.h++>
#include <string>

#include "Core.hpp"

namespace rtx::core {

class Config {
    public:
        Config();

//        Config(const Config &) = default;
//        Config(Config &&) = default;


        ~Config() = default;

        Config(const std::string &path);

        void readFile(const std::string &path);

        Core initCore();
    private:
        libconfig::Config _config;
};

}  // namespace rtx::core
