/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Rectangle.hpp
*/

#pragma once

#include "Point.hpp"
#include "Vector.hpp"

namespace rtx::maths {
template <typename T>
class Rectangle2 {
   public:
    Rectangle2(Point2<T> point, Vector2<T> size) : _point{point}, _size{size} {}

    Point2<T> &point() {
        return _point;
    }
    [[nodiscard]] const Point2<T> &point() const {
        return _point;
    }

    Vector2<T> &size() {
        return _size;
    }
    [[nodiscard]] const Vector2<T> &size() const {
        return _size;
    }

   private:
    Point2<T> _point;
    Vector2<T> _size;
};

template <typename T>
class Rectangle3 {
   public:
    Rectangle3() = default;
    Rectangle3(Point3<T> a, Point3<T> b, Point3<T> d)
        : _a{a}, _b{b}, _d{d}, _c(b + a.vectorTo(d)) {};

    Vector2<T> size() {
        return {_a.vectorTo(_b).length(), _a.vectorTo(_d).length()};
    }

    Point3<T> center() {
        return {_a + _a.vectorTo(_b) / 2, _a + _a.vectorTo(_d) / 2};
    }

    Point3<T> a() {
        return _a;
    }
    Point3<T> b() {
        return _b;
    }
    Point3<T> c() {
        return _c;
    }
    Point3<T> d() {
        return _d;
    }

   private:
    Point3<T> _a;
    Point3<T> _b;
    Point3<T> _d;
    Point3<T> _c;
};
}  // namespace rtx::maths
