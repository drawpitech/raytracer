/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Viewport.hpp
*/

#pragma once

#include <rtx/maths/Point.hpp>
#include <rtx/maths/Ray.hpp>
#include <rtx/maths/Rectangle.hpp>

namespace rtx::scene {

class Viewport {
   public:
    Viewport(
        maths::Rectangle3<double> rect,
        maths::Vector2<std::size_t> resolution,
        maths::Point3<double> position
    );

    [[nodiscard]] maths::Ray3<double> ray(maths::Point2<double> point) const;

   private:
    // maths::Rectangle3<double> _rect;
    maths::Point3<double> _origin;
    maths::Vector2<std::size_t> _size;
    maths::Point3<double> _position;
    maths::Vector3<double> _down;
    maths::Vector3<double> _right;
};

}  // namespace rtx::scene
