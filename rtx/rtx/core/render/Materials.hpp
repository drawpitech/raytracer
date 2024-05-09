/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Materials.hpp
*/

#pragma once
#include <rtx/core/others/Scene.hpp>
#include <rtx/core/render/Color.hpp>

#include "Hitpoint.hpp"

namespace rtx::render {

class Materials {
   public:
    explicit Materials(const Color &diffuse);

    [[nodiscard]] Color render(const Hitpoint &hitpoint, const others::ThreadedScene &scene) const;

    [[nodiscard]] Color fastRender(const Hitpoint &hitpoint, const others::ThreadedScene &scene)
        const;

   private:
    Color _diffuse;
};

}  // namespace rtx::render
