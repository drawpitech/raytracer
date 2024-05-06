/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Hitpoint.hpp
*/

#pragma once

#include <rtx/maths/Ray.hpp>

namespace rtx::core {

class Hitpoint {
   public:
    Hitpoint(
        const maths::Ray3<double> &ray, double distance,
        const maths::Point3<double> &point,
        const maths::Vector3<double> &normal);

    [[nodiscard]] const maths::Ray3<double> &ray() const;
    [[nodiscard]] const double &distance() const;
    [[nodiscard]] const maths::Point3<double> &point() const;
    [[nodiscard]] const maths::Vector3<double> &normal() const;

   private:
    maths::Ray3<double> _ray;

    double _distance;

    maths::Point3<double> _point;

    maths::Vector3<double> _normal;
};

}  // namespace rtx::core
