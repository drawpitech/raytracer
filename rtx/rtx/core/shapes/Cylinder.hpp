/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder.hpp
*/

#pragma once
#include <rtx/core/render/Material.hpp>
#include <rtx/maths/Point.hpp>
#include <rtx/maths/Vector.hpp>

#include "AObject.hpp"
#include "Disk.hpp"

namespace rtx::shapes {

class Cylinder : public AObject {
   public:
    Cylinder(
        const maths::Vector3<double> &axis,
        const maths::Point3<double> &position,
        const double radius,
        const double height,
        const render::Material &material
    );

    [[nodiscard]] std::optional<render::Hitpoint> hit(const maths::Ray3<double> &ray
    ) const override;

    [[nodiscard]] const render::Material &material() const override;

   private:
    maths::Vector3<double> _axis;
    maths::Point3<double> _position;
    double _radius;
    double _height;
    render::Material _material;
    Disk _bottom_disk;
    Disk _top_disk;

    [[nodiscard]] std::optional<render::Hitpoint> hit_surface(const maths::Ray3<double> &ray) const;
};

}  // namespace rtx::shapes
