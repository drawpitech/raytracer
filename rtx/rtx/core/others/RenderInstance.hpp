/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RenderingInstance.hpp
*/

#pragma once

#include <rtx/core/others/Viewport.hpp>

#include "Image.hpp"
#include "RenderCluster.hpp"
#include "Scene.hpp"

namespace rtx::others {

class RenderInstance {
   public:
    RenderInstance(
        const ThreadedScene &scene,
        const Viewport &viewport,
        maths::Vector2<std::size_t> resolution
    );

    ~RenderInstance() = default;

    RenderInstance(const RenderInstance &) = delete;
    RenderInstance(RenderInstance &&) = delete;

    RenderInstance &operator=(const RenderInstance &) = delete;
    RenderInstance &operator=(RenderInstance &&) = delete;

    [[nodiscard]] others::RenderCluster
    renderCluster(maths::Point2<size_t> topleft, maths::Vector2<size_t> bottomright);

    [[nodiscard]] const Image &image() const;

   private:
    const ThreadedScene *_scene;
    maths::Vector2<std::size_t> _resolution;
    Viewport _viewport;
    Image _image;
};

}  // namespace rtx::others
