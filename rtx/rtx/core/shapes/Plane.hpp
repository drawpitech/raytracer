/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane.hpp
*/

#pragma once
#include <rtx/core/render/Material.hpp>

#include "AObject.hpp"

namespace rtx::shapes {

class Plane : public rtx::shapes::AObject {
   public:
    Plane(
        const maths::Vector3<double> &normal,
        const maths::Point3<double> &p,
        const render::Material &material
    );

    [[nodiscard]] std::optional<render::Hitpoint> hit(const maths::Ray3<double> &ray
    ) const override;

    [[nodiscard]] const render::Material &material() const override;

   private:
    maths::Vector3<double> _normal;
    maths::Point3<double> _origin;
    render::Material _material;
};

}  // namespace rtx::shapes
