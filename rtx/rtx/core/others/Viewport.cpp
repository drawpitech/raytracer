/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Viewport.cpp
*/

#include "Viewport.hpp"

#include <iostream>

namespace rtx::others {
Viewport::Viewport(
    maths::Rectangle3<double> rect,
    maths::Vector2<std::size_t> resolution,
    maths::Point3<double> position
)
    : _origin{rect.a()},
      _size{resolution},
      _position{position},
      _down{rect.a().vectorTo(rect.d()) / resolution.y()},
      _right{rect.a().vectorTo(rect.b()) / resolution.x()} {}

maths::Ray3<double> Viewport::ray(maths::Point2<double> point) const {
    if (point.x() < 0 || point.x() > static_cast<double>(_size.x()) + 1 || point.y() < 0 ||
        point.y() > static_cast<double>(_size.y()) + 1) {
        std::clog << "Generated ray is out of the viewport\n";
    }

    return {_position, _position.vectorTo(_origin + _down * (point.y()) + _right * (point.x()))};
}
}  // namespace rtx::others
