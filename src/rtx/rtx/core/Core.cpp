/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Core.cpp
*/

#include "Core.hpp"

#include <iostream>

namespace rtx::core {
Core::Core() {
    std::clog << "Core:\tInitializing...\n";
}

void Core::render() {
    std::clog << "Core:\tRendering...\n";
}

void Core::setScene(const Scene& scene) {
    _scene = scene;
}
}  // namespace rtx::core
