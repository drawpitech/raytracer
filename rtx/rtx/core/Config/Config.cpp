/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Config.cpp
*/

#include "Config.hpp"

#include <iostream>

namespace rtx::core {

Config::Config(const std::string &path) {
    readFile(path);
}

void Config::readFile(const std::string &path) {
    std::clog << "Config:\tLoading config in \"" << path << "\"...\n";
    _config.readFile(path);
}

}  // namespace rtx::core
