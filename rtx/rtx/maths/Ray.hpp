/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Ray.hpp
*/

#pragma once

#include <ostream>

#include "Point.hpp"
#include "Vector.hpp"

namespace rtx::maths {

template <typename T>
class Ray3 {
   public:
    Ray3(Point3<T> origin, Vector3<T> direction) : _origin{origin}, _direction{direction.normalized()} {}

    Point3<T> &origin() {
        return _origin;
    }

    [[nodiscard]] const Point3<T> &origin() const {
        return _origin;
    }

    Vector3<T> &direction() {
        return _direction;
    }

    [[nodiscard]] const Vector3<T> &direction() const {
        return _direction;
    }

    friend std::ostream &operator<<(std::ostream &os, const Ray3 &r) {
        return os << "(" << r.origin() << ", " << r.direction() << ")";
    }

   private:
    Point3<T> _origin;
    Vector3<T> _direction;
};

}  // namespace rtx::maths
