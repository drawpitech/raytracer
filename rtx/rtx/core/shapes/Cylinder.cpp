/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder.cpp
*/

#include "Cylinder.hpp"

#include <iostream>

namespace rtx::shapes {
Cylinder::Cylinder(
    const maths::Vector3<double> &axis,
    const maths::Point3<double> &position,
    const double radius,
    const double height,
    const render::Material &material
)
    : _axis{axis.normalized()},
      _position{position},
      _radius{radius},
      _height{height},
      _material{material},
      _bottom_disk{_axis, _position, _radius, _material},
      _top_disk{_axis, _position + (_axis * _height), _radius, _material} {}

std::optional<render::Hitpoint> Cylinder::hit(const maths::Ray3<double> &ray) const {
    std::optional<render::Hitpoint> hitpoint;
    double t = std::numeric_limits<double>::infinity();

    if (const auto s_hitpoint = hit_surface(ray); s_hitpoint && s_hitpoint->distance() < t) {
        t = s_hitpoint->distance();
        hitpoint = s_hitpoint;
    }

    if (auto t_hitpoint = _top_disk.hit(ray); t_hitpoint && t_hitpoint->distance() < t) {
        t = t_hitpoint->distance();
        hitpoint = {
            t_hitpoint->ray(),
            t_hitpoint->distance(),
            t_hitpoint->point(),
            t_hitpoint->normal(),
            *this
        };
    }

    if (const auto b_hitpoint = _bottom_disk.hit(ray); b_hitpoint && b_hitpoint->distance() < t) {
        hitpoint = {
            b_hitpoint->ray(),
            b_hitpoint->distance(),
            b_hitpoint->point(),
            b_hitpoint->normal(),
            *this
        };
    }

    return hitpoint;
}

const render::Material &Cylinder::material() const {
    return _material;
}

std::optional<render::Hitpoint> Cylinder::hit_surface(const maths::Ray3<double> &ray) const {
    const auto raynormal = ray.direction();
    const auto na = raynormal.cross(_axis);
    const auto b = ray.origin().vectorTo(_position);
    const auto delta =
        na.normSquared() * _radius * _radius - _axis.normSquared() * std::pow(b.dot(na), 2);

    if (delta < 0) {
        return {};
    }

    const auto ba = na.dot(b.cross(_axis));

    const auto sd = std::sqrt(delta);

    const auto d = ba > sd ? (ba - sd) / na.normSquared() : (ba + sd) / na.normSquared();
    auto t = _axis.dot(raynormal * d - b);

    if (d < 0) {
        return {};
    }

    if (t < 0 || t > _height) {
        return {};
    }

    const auto normal = (raynormal * d - _axis * t - b);

    return render::Hitpoint{ray, d, ray.origin() + ray.direction() * d, normal, *this};
}
}  // namespace rtx::shapes
