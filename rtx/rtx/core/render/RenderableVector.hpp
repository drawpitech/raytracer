/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RenderableVector.hpp
*/

#pragma once

#include <vector>

#include "IObject.hpp"
#include "Renderable.hpp"

namespace rtx::render {

class RenderableVector final : public IRenderable, public std::vector<const IObject *> {
   public:
    [[nodiscard]] std::optional<Hitpoint> hit(const maths::Ray3<double> &ray) const override;

    [[nodiscard]] std::optional<Hitpoint>
    hit(const maths::Ray3<double> &ray, const IRenderable &ignore) const override;
};

}  // namespace rtx::render
