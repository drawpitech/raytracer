/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere.cpp
*/

#include "Sphere.hpp"

namespace rtx::render {

Sphere::Sphere(const maths::Point3<double> &center, double radius, const Materials &material)
    : _center{center}, _radius{radius}, _material{material} {}

std::optional<render::Hitpoint> Sphere::hit(const maths::Ray3<double> &ray) const {
    const auto oc = ray.origin().vectorTo(_center);
    const auto a = ray.direction().normSquared();
    const auto h = ray.direction().dot(oc);
    const auto c = oc.normSquared() - _radius * _radius;

    const auto delta = h * h - a * c;
    if (delta < 0) {
        return {};
    }

    const auto sd = std::sqrt(delta);
    const auto t = (sd < h) ? (h - sd) / a : (h + sd) / a;

    if (t < 0) {
        return {};
    }

    const auto direction = _radius > oc.norm() ? -1 : 1;
    const maths::Point3 point = ray.origin() + (ray.direction() * t);
    return render::Hitpoint{
        ray, t, point, (_center.vectorTo(point) * direction).normalized(), *this
    };
}

std::optional<render::Hitpoint>
Sphere::hit(const maths::Ray3<double> &ray, const IRenderable &ignore) const {
    if (&ignore == this) {
        return {};
    }
    return hit(ray);
}

const render::Materials &Sphere::material() const {
    return _material;
}

}  // namespace rtx::render
