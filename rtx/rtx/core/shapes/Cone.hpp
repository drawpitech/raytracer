/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cone.hpp
*/

#pragma once
#include "AObject.hpp"
#include "Disk.hpp"
#include "Plane.hpp"

namespace rtx::shapes {

class Cone : public AObject {
   public:
    Cone(
        const maths::Vector3<double> &axis,
        const maths::Point3<double> &position,
        const double radius,
        const render::Material &material
    )
        : _axis{axis},
          _position{position},
          _radius{radius},
          _material{material},
          _disk{_axis, _position, _radius, _material} {}

    [[nodiscard]] std::optional<render::Hitpoint> hit(const maths::Ray3<double> &ray
    ) const override;

    [[nodiscard]] const render::Material &material() const override;

   private:
    maths::Vector3<double> _axis;
    maths::Point3<double> _position;
    double _radius;
    render::Material _material;
    Disk _disk;

    maths::Vector3<double> getNormal(maths::Point3<double> p, maths::Point3<double> apex) const;

    [[nodiscard]] std::optional<render::Hitpoint> hit_surface(const maths::Ray3<double> &ray) const;
    [[nodiscard]] std::optional<render::Hitpoint> hit_bottom(const maths::Ray3<double> &ray) const;
};
}  // namespace rtx::shapes
