/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** DirectionalLights.hpp
*/

#pragma once
#include <rtx/maths/Vector.hpp>

#include "Color.hpp"

namespace rtx::render {

class DirectionalLights {
   public:
    DirectionalLights(maths::Vector3<double> direction, double intensity, render::Color color);

    [[nodiscard]] maths::Vector3<double> direction() const;
    [[nodiscard]] double intensity() const;
    [[nodiscard]] render::Color color() const;

   private:
    maths::Vector3<double> _direction;
    double _intensity;
    render::Color _color;
};

}  // namespace rtx::render
