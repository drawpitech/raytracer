/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane.cpp
*/

#include "Plane.hpp"

namespace rtx::render {

Plane::Plane(
    const maths::Vector3<double> &normal,
    const maths::Point3<double> &p,
    const Materials &material
)
    : _normal{normal}, _origin{p}, _material{material} {}

std::optional<Hitpoint> Plane::hit(const maths::Ray3<double> &ray) const {
    auto dot = ray.direction().dot(_normal);
    if (dot == 0) {
        return {};
    }

    double d = ray.origin().vectorTo(_origin).dot(_normal) / ray.direction().dot(_normal);

    // std::cerr << "d: " << d << std::endl;
    return Hitpoint{
        ray, d, ray.origin() + ray.direction() * d, _normal * (dot < 0 ? 1. : -1.), *this
    };
}

std::optional<Hitpoint> Plane::hit(const maths::Ray3<double> &ray, const IRenderable &ignore)
    const {
    if (&ignore == this) {
        return {};
    }
    return hit(ray);
}

const Materials &Plane::material() const {
    return _material;
}
}  // namespace rtx::render
