/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere.hpp
*/

#pragma once
#include "IObject.hpp"
#include "Materials.hpp"

namespace rtx::render {

class Sphere : public render::IObject {
   public:
    Sphere(const maths::Point3<double> &center, double radius, const render::Materials &material);

    [[nodiscard]] std::optional<render::Hitpoint> hit(const maths::Ray3<double> &ray
    ) const override;

    [[nodiscard]] std::optional<render::Hitpoint>
    hit(const maths::Ray3<double> &ray, const IRenderable &ignore) const override;

    [[nodiscard]] const render::Materials &material() const override;

   private:
    maths::Point3<double> _center;
    double _radius;
    render::Materials _material;
};

}  // namespace rtx::render
