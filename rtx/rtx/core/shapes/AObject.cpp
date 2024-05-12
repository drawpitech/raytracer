/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** AObject.cpp
*/

#include "AObject.hpp"

namespace rtx::shapes {
std::optional<render::Hitpoint>
AObject::hit_ignore(const maths::Ray3<double> &ray, const IRenderable &ignore) const {
    if (&ignore == this) {
        return {};
    }
    return hit(ray);
}
}  // namespace rtx::shapes
