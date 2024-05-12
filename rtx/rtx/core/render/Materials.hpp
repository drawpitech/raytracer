/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Materials.hpp
*/

#pragma once
#include <rtx/core/render/Color.hpp>
#include <rtx/core/scene/Scene.hpp>

#include "Hitpoint.hpp"

namespace rtx::render {

class Materials {
   public:
    explicit Materials(const Color &diffuse);

    [[nodiscard]] Color render(const Hitpoint &hitpoint, const scene::SceneRef &scene) const;

    [[nodiscard]] Color fastRender(const Hitpoint &hitpoint, const scene::SceneRef &scene) const;

   private:
    Color _diffuse;
};

}  // namespace rtx::render
