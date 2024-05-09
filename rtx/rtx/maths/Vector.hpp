/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Vector.hpp
*/

#pragma once

#include <cmath>
#include <ostream>
#include <stdexcept>
#include <string>

#include "maths_concepts.hpp"

namespace rtx::maths {

template <typename T>
    requires std::is_arithmetic_v<T>
class Vector3 {
   public:
    constexpr Vector3() = default;

    constexpr Vector3(T x, T y, T z) : _x(x), _y(y), _z(z) {}

    T &at(const std::string &i) {
        if (i == "x") {
            return _x;
        }
        if (i == "y") {
            return _y;
        }
        if (i == "z") {
            return _z;
        }
        throw std::out_of_range("Vector3::at: invalid index");
    }

    constexpr T at(const std::string &i) const {
        if (i == "x") {
            return _x;
        }
        if (i == "y") {
            return _y;
        }
        if (i == "z") {
            return _z;
        }
        throw std::out_of_range("Vector3::at: invalid index");
    }

    constexpr T x() const {
        return _x;
    }

    constexpr T y() const {
        return _y;
    }

    constexpr T z() const {
        return _z;
    }

    T &x() {
        return _x;
    }

    T &y() {
        return _y;
    }

    T &z() {
        return _z;
    }

    template <Addable<T> U>
    constexpr Vector3<addition_result_t<T, U>> operator+(const Vector3<U> &v) const {
        return {_x + v.x(), _y + v.y(), _z + v.z()};
    }

    template <Substractable<T> U>
    constexpr Vector3<substraction_result_t<T, U>> operator-(const Vector3<U> &v) const {
        return {_x - v.x(), _y - v.y(), _z - v.z()};
    }

    constexpr Vector3 operator-() const {
        return {-_x, -_y, -_z};
    }

    template <Multiplicable<T> U>
    constexpr Vector3<multiplication_result_t<T, U>> operator*(const U v) const {
        return {_x * v, _y * v, _z * v};
    }

    template <Divisable<T> U>
    constexpr Vector3<division_result_t<T, U>> operator/(const U v) const {
        return {_x / v, _y / v, _z / v};
    }

    template <Multiplicable<T> U>
    constexpr multiplication_result_t<T, U> dot(const Vector3<U> &v) const {
        return _x * v.x() + _y * v.y() + _z * v.z();
    }

    constexpr T norm() const {
        return std::sqrt(_x * _x + _y * _y + _z * _z);
    }

    constexpr T normSquared() const {
        return _x * _x + _y * _y + _z * _z;
    }

    [[nodiscard]] constexpr bool isNormalized() const {
        return std::fabs(normSquared() - 1) < std::numeric_limits<double>::epsilon();
    }

    constexpr Vector3 normalized() const {
        return *this / norm();
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector3 &v) {
        return os << '(' << v.x() << ", " << v.y() << ", " << v.z() << ')';
    }

   private:
    T _x;
    T _y;
    T _z;
};

template <typename T>
    requires std::is_arithmetic_v<T>
class Vector2 {
   public:
    Vector2(std::initializer_list<T> l) {
        auto it = l.begin();
        if (it != l.end()) {
            _x = *it;
        }
        if (++it != l.end()) {
            _y = *it;
        }
        if (++it != l.end()) {
            throw std::out_of_range("Vector3: too many arguments");
        }
    }

    Vector2(T x, T y) : _x(x), _y(y) {}

    template <typename U>
    explicit Vector2(const Vector2<U> &v) : _x(v.x()), _y(v.y()) {}

    T &at(const std::string &i) {
        if (i == "x") {
            return _x;
        }
        if (i == "y") {
            return _y;
        }
        throw std::out_of_range("Vector3::at: invalid index");
    }

    const T &at(const std::string &i) const {
        if (i == "x") {
            return _x;
        }
        if (i == "y") {
            return _y;
        }
        throw std::out_of_range("Vector3::at: invalid index");
    }

    const T &x() const {
        return _x;
    }

    const T &y() const {
        return _y;
    }

    T &x() {
        return _x;
    }

    T &y() {
        return _y;
    }

    template <Addable<T> U>
    Vector2<addition_result_t<T, U>> operator+(const Vector2<U> &v) const {
        return {_x + v.x(), _y + v.y()};
    }

    template <NonNarrowingConvertibleTo<T> U>
    Vector2 &operator+=(const Vector2<U> &v) {
        _x += v.x();
        _y += v.y();
        return *this;
    }

    template <Substractable<T> U>
    Vector2<substraction_result_t<T, U>> operator-(const Vector2<U> &v) const {
        return {_x - v.x(), _y - v.y()};
    }

    template <NonNarrowingConvertibleTo<T> U>
    Vector2 &operator-=(const Vector2<U> &v) {
        _x -= v.x();
        _y -= v.y();
        return *this;
    }

    template <Multiplicable<T> U>
    Vector2<multiplication_result_t<T, U>> operator*(U v) const {
        return {_x * v, _y * v};
    }

    template <NonNarrowingConvertibleTo<T> U>
    Vector2 &operator*=(U v) {
        _x *= v;
        _y *= v;
        return *this;
    }

    template <Divisable<T> U>
    Vector2<division_result_t<T, U>> operator/(U &v) const {
        return {_x / v, _y / v};
    }

    template <NonNarrowingConvertibleTo<T> U>
    Vector2 &operator/=(U v) {
        _x /= v;
        _y /= v;
        return *this;
    }

    template <Multiplicable<T> U>
    multiplication_result_t<T, U> dot(const Vector2<U> &v) const {
        return _x * v.x() + _y * v.y();
    }

    T norm() const {
        return std::sqrt(_x * _x + _y * _y);
    }

    T normSquared() const {
        return _x * _x + _y * _y;
    }

    constexpr Vector2 normalized() const {
        return *this / norm();
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector2 &v) {
        return os << "(" << v.x() << ", " << v.y() << ")";
    }

   private:
    T _x;
    T _y;
};

}  // namespace rtx::maths
