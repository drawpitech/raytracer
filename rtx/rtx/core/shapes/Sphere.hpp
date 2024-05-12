/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere.hpp
*/

#pragma once
#include <rtx/core/render/Material.hpp>

#include "AObject.hpp"

namespace rtx::shapes {

class Sphere : public AObject {
   public:
    Sphere(const maths::Point3<double> &center, double radius, const render::Material &material);

    [[nodiscard]] std::optional<render::Hitpoint> hit(const maths::Ray3<double> &ray
    ) const override;

    [[nodiscard]] const render::Material &material() const override;

   private:
    maths::Point3<double> _center;
    double _radius;
    render::Material _material;
};

}  // namespace rtx::shapes
