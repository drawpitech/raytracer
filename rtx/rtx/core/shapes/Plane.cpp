/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane.cpp
*/

#include "Plane.hpp"

namespace rtx::shapes {

Plane::Plane(
    const maths::Vector3<double> &normal,
    const maths::Point3<double> &p,
    const render::Material &material
)
    : _normal{normal.normalized()}, _origin{p}, _material{material} {}

std::optional<render::Hitpoint> Plane::hit(const maths::Ray3<double> &ray) const {
    const auto dot = ray.direction().dot(_normal);
    if (dot == 0) {
        return {};
    }

    const double d = ray.origin().vectorTo(_origin).dot(_normal) / dot;

    return render::Hitpoint{
        ray, d, ray.origin() + ray.direction() * d, _normal * (dot < 0 ? 1. : -1.), *this
    };
}

const render::Material &Plane::material() const {
    return _material;
}
}  // namespace rtx::shapes
