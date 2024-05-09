/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane.hpp
*/

#pragma once
#include "IObject.hpp"
#include "Materials.hpp"

namespace rtx::render {

class Plane : public IObject {
   public:
    Plane(
        const maths::Vector3<double> &normal,
        const maths::Point3<double> &p,
        const Materials &material
    );

    [[nodiscard]] std::optional<Hitpoint> hit(const maths::Ray3<double> &ray) const override;

    [[nodiscard]] std::optional<Hitpoint>
    hit(const maths::Ray3<double> &ray, const IRenderable &ignore) const override;

    [[nodiscard]] const Materials &material() const override;

   private:
    maths::Vector3<double> _normal;
    maths::Point3<double> _origin;
    Materials _material;
};

}  // namespace rtx::render
