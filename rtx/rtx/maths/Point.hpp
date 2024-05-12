/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Point.hpp
*/

#pragma once
#include "Matrix.hpp"
#include "Vector.hpp"

namespace rtx::maths {

template <typename T>
class Point3 {
   public:
    constexpr Point3() = default;

    constexpr Point3(T x, T y, T z) : _x{x}, _y{y}, _z{z} {}

    T &x() {
        return _x;
    }

    [[nodiscard]] const T &x() const {
        return _x;
    }

    T &y() {
        return _y;
    }

    [[nodiscard]] const T &y() const {
        return _y;
    }

    T &z() {
        return _z;
    }

    [[nodiscard]] const T &z() const {
        return _z;
    }

    Point3 operator+(const Vector3<T> &p) const {
        return {_x + p.x(), _y + p.y(), _z + p.z()};
    }

    Point3 operator-(const Vector3<T> &p) const {
        return {_x - p.x(), _y - p.y(), _z - p.z()};
    }

    template <Substractable<T> U>
    Vector3<substraction_result_t<T, U>> operator-(Point3<U> p) const {
        return {_x - p.x(), _y - p.y(), _z - p.z()};
    }

    Vector3<T> vectorTo(const Point3 &p) const {
        return {p.x() - _x, p.y() - _y, p.z() - _z};
    }

    Matrix<T, 4, 1> toMatrix() const {
        return {_x, _y, _z, 1};
    };

   private:
    T _x;
    T _y;
    T _z;
};

constexpr Point3<double> VORIGIN{0, 0, 0};

template <typename T>
class Point2 {
   public:
    Point2(T x, T y) : _x{x}, _y{y} {}

    T &x() {
        return _x;
    }

    [[nodiscard]] const T &x() const {
        return _x;
    }

    T &y() {
        return _y;
    }

    [[nodiscard]] const T &y() const {
        return _y;
    }

    Matrix<T, 3, 1> toMatrix() const {
        return {_x, _y, 1};
    }

   private:
    T _x;
    T _y;
};

}  // namespace rtx::maths
