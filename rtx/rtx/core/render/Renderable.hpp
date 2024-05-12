/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Renderable.hpp
*/

#pragma once
#include <rtx/maths/Ray.hpp>

#include <optional>

#include "Hitpoint.hpp"

namespace rtx::render {

class IRenderable {
   public:
    virtual ~IRenderable() = default;

    [[nodiscard]] virtual std::optional<Hitpoint> hit(const maths::Ray3<double> &ray) const = 0;

    [[nodiscard]] virtual std::optional<Hitpoint>
    hit_ignore(const maths::Ray3<double> &ray, const IRenderable &ignore) const = 0;
};

}  // namespace rtx::render
