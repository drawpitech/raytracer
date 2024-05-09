/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Intervals.hpp
*/

#pragma once

#include <algorithm>
#include <type_traits>

namespace rtx::maths {

template <typename T>
    requires std::is_arithmetic_v<T>
class Intervals {
   public:
    Intervals(T min, T max) : _min(min), _max(max) {}

    const T &min() const {
        return _min;
    }

    const T &max() const {
        return _max;
    }

    T &min() {
        return _min;
    }

    T &max() {
        return _max;
    }

    bool contains(const T &value) const {
        return value >= _min && value <= _max;
    }

    T clamp(const T &value) const {
        return std::clamp(value, _min, _max);
    }

   private:
    T _min;
    T _max;
};

}  // namespace rtx::maths
