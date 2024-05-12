/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Shape.hpp
*/

#pragma once
#include <rtx/core/render/Renderable.hpp>


namespace rtx::render {
class Material;
}

namespace rtx::shapes {
class AObject : public render::IRenderable {
   public:
    ~AObject() override = default;

    [[nodiscard]] std::optional<render::Hitpoint>
    hit_ignore(const maths::Ray3<double> &ray, const IRenderable &ignore) const final;

    [[nodiscard]] virtual const render::Material &material() const = 0;
};
}  // namespace rtx::shapes
