/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RenderableVector.hpp
*/

#pragma once

#include <rtx/core/render/Renderable.hpp>
#include <rtx/core/shapes/AObject.hpp>

#include <vector>


namespace rtx::render {

class RenderableVector final : public IRenderable, public std::vector<const shapes::AObject *> {
   public:
    [[nodiscard]] std::optional<Hitpoint> hit(const maths::Ray3<double> &ray) const override;

    [[nodiscard]] std::optional<Hitpoint>
    hit_ignore(const maths::Ray3<double> &ray, const IRenderable &ignore) const override;
};

}  // namespace rtx::render
