/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Shape.hpp
*/

#pragma once
#include "Renderable.hpp"

namespace rtx::render {
class Materials;
}

namespace rtx::render {

class IObject : public IRenderable {
   public:
    ~IObject() override = default;

    [[nodiscard]] virtual const Materials &material() const = 0;
};

}  // namespace rtx::render
