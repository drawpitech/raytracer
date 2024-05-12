/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** InfiniteCylinder.hpp
*/

#pragma once
#include <rtx/core/render/Material.hpp>

#include "AObject.hpp"

namespace rtx::shapes {

class InfiniteCylinder : public AObject {
   public:
    InfiniteCylinder(
        const maths::Vector3<double> &axis,
        const maths::Point3<double> &position,
        const double radius,
        const render::Material &material
    );

    [[nodiscard]] std::optional<render::Hitpoint> hit(const maths::Ray3<double> &ray
    ) const override;

    [[nodiscard]] const render::Material &material() const override;

   private:
    maths::Vector3<double> _axis;
    maths::Point3<double> _position;
    double _radius;
    render::Material _material;
};

}  // namespace rtx::shapes

// rtx
