/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** AmbientLight.hpp
*/

#pragma once
#include "Color.hpp"

namespace rtx::render {

struct AmbientLight {
    Color color{0, 0, 0};
    double intensity{0};
};

}  // namespace rtx::render
