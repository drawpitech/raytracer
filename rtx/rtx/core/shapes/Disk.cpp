/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Disk.cpp
*/

#include "Disk.hpp"

namespace rtx::shapes {
Disk::Disk(
    const maths::Vector3<double> &axis,
    const maths::Point3<double> &position,
    const double radius,
    const render::Material &material
)
    : _axis{axis.normalized()},
      _position{position},
      _radius{radius},
      _material{material},
      _plane{_axis, _position, _material} {}

std::optional<render::Hitpoint> Disk::hit(const maths::Ray3<double> &ray) const {
    const auto hitpoint = _plane.hit(ray);
    if (!hitpoint || hitpoint->point().vectorTo(_position).norm() > _radius) {
        return {};
    }
    return hitpoint;
}

const render::Material &Disk::material() const {
    return _material;
}
}  // namespace rtx::shapes
