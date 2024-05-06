/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere.hpp
*/

#pragma once
#include <rtx/core/Object/Object.hpp>

namespace rtx::basics {

class Sphere : public core::Object {
   public:
    Sphere(const maths::Point3<double>& center, double radius);

    [[nodiscard]] std::optional<core::Hitpoint> hit(
        const maths::Ray3<double>& ray) const override;

   private:
    maths::Point3<double> _center;
    double _radius;
};

}  // namespace rtx::basics
