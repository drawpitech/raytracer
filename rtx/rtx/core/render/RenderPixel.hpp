/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RayRender.hpp
*/

#pragma once

#include <rtx/core/scene/Scene.hpp>
#include <rtx/core/scene/Viewport.hpp>
#include <rtx/maths/Ray.hpp>

#include "Color.hpp"

namespace rtx::render {

class RenderPixel {
   public:
    RenderPixel(const scene::SceneRef &scene, const scene::Viewport &viewport)
        : _scene(&scene), _viewport{viewport} {}

    [[nodiscard]] Color render(maths::Point2<size_t> point) const;

   private:
    const scene::SceneRef *_scene;
    scene::Viewport _viewport;

    [[nodiscard]] Color renderRay(const maths::Ray3<double> &ray) const;
};

}  // namespace rtx::render
