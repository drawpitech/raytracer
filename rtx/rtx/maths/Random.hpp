/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Random.hpp
*/

#pragma once
#include <concepts>
#include <random>

#include "Vector.hpp"

namespace rtx::maths {

class Random {
    template <typename T>
    static T generate(T min, T max) {
        T nb = _generator();
        return min + (max - min) * ((nb - std::ranlux48_base::min()) /
                                    (std::ranlux48_base::max() - std::ranlux48_base::min()));
    }

   public:
    template <std::floating_point T>
    static Vector3<T> randomVector3() {
        return Vector3<T>{generate(1, -1), generate(1, -1), generate(1, -1)};
    }

    template <std::floating_point T>
    static Vector3<T> randomVector3(T min, T max) {
        std::uniform_real_distribution<T> distribution(min, max);
        return Vector3<T>{generate<T>(min, max), generate<T>(min, max), generate<T>(min, max)};
    }

    template <std::floating_point T>
    static Vector3<T> randomUnitVector3() {
        std::uniform_real_distribution<T> distribution(-1, 1);
        return Vector3<T>{generate<T>(-1, 1), generate<T>(-1, 1), generate<T>(-1, 1)}.normalized();
    }

    template <std::floating_point T>
    static double randomDouble(T min, T max) {
        auto ng = generate(min, max);
        return ng;
    }

   private:
    inline static thread_local std::ranlux48_base _generator{std::random_device{}()};
};

}  // namespace rtx::maths
