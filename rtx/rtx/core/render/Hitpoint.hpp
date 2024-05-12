/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Hitpoint.hpp
*/

#pragma once

#include <rtx/maths/Ray.hpp>

namespace rtx::shapes {
class AObject;
}

namespace rtx::render {
class Hitpoint {
   public:
    Hitpoint(
        const maths::Ray3<double> &ray,
        double distance,
        const maths::Point3<double> &point,
        const maths::Vector3<double> &normal,
        const shapes::AObject &object
    );

    [[nodiscard]] const maths::Ray3<double> &ray() const;
    [[nodiscard]] const double &distance() const;
    [[nodiscard]] const maths::Point3<double> &point() const;
    [[nodiscard]] const maths::Vector3<double> &normal() const;
    [[nodiscard]] const shapes::AObject &object() const;

   private:
    maths::Ray3<double> _ray;
    double _distance;
    maths::Point3<double> _point;
    maths::Vector3<double> _normal;
    const shapes::AObject *_object;
};

}  // namespace rtx::render
