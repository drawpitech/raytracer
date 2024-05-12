/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** InfiniteCylinder.cpp
*/

#include "InfiniteCylinder.hpp"

namespace rtx::shapes {

InfiniteCylinder::InfiniteCylinder(
    const maths::Vector3<double> &axis,
    const maths::Point3<double> &position,
    const double radius,
    const render::Material &material
)
    : _axis{axis.normalized()}, _position{position}, _radius{radius}, _material{material} {}

std::optional<render::Hitpoint> InfiniteCylinder::hit(const maths::Ray3<double> &ray) const {
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
    const auto t = _axis.dot(raynormal * d - b);

    if (d < 0) {
        return {};
    }

    const auto normal = (raynormal * d - _axis * t - b);

    return render::Hitpoint{ray, d, ray.origin() + ray.direction() * d, normal, *this};
}

const render::Material &InfiniteCylinder::material() const {
    return _material;
}
}  // namespace rtx::shapes

// rtx
