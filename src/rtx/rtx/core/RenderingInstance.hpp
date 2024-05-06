/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RenderingInstance.hpp
*/

#pragma once
#include <rtx/basics/Viewport.hpp>

#include "Image.hpp"
#include "Scene.hpp"

namespace rtx::core {

class RenderingInstance {
   public:
    RenderingInstance(
        const basics::Viewport &viewport,
        maths::Vector2<std::size_t> resolution);

    void setScene(const Scene &scene);

    void render();

    [[nodiscard]] const Image &image() const;

   private:
    maths::Vector2<std::size_t> _resolution;
    basics::Viewport _viewport;
    const Scene *_scene = nullptr;
    Image _image;
};

}  // namespace rtx::core
