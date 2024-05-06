/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Shape.hpp
*/

#pragma once
#include <optional>

#include "Hitpoint.hpp"

namespace rtx::core {

class Object {
   public:
    Object() = default;

    Object(const Object &) = default;
    Object(Object &&) = default;

    Object &operator=(const Object &) = default;
    Object &operator=(Object &&) = default;

    virtual ~Object() = default;

    [[nodiscard]] virtual std::optional<Hitpoint> hit(
        const maths::Ray3<double> &ray) const = 0;
};

}  // namespace rtx::core
