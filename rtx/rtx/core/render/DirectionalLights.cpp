/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** DirectionalLights.cpp
*/

#include "DirectionalLights.hpp"

namespace rtx::render {

DirectionalLight::DirectionalLight(
    maths::Vector3<double> direction,
    double intensity,
    render::Color color
)
    : _direction{direction.normalized()}, _intensity{intensity}, _color{color} {}

maths::Vector3<double> DirectionalLight::direction() const {
    return _direction;
}

double DirectionalLight::intensity() const {
    return _intensity;
}

render::Color DirectionalLight::color() const {
    return _color;
}
}  // namespace rtx::render
