/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RenderCluster.hpp
*/

#pragma once
#include <rtx/core/others/Image.hpp>
#include <rtx/core/others/Viewport.hpp>
#include <rtx/maths/Point.hpp>

#include "Scene.hpp"

namespace rtx::others {

class RenderCluster {
   public:
    // RenderCluster &operator=(const RenderCluster &) = delete;
    // RenderCluster &operator=(RenderCluster &&) = delete;

    RenderCluster(
        maths::Rectangle2<size_t> rect,
        Image &image,
        Viewport &viewport,
        const ThreadedScene &scene
    )
        : _rect{rect}, _viewport{&viewport}, _image{&image}, _scene{&scene} {}

    void render() const;

   private:
    maths::Rectangle2<size_t> _rect;
    Viewport *_viewport;
    Image *_image;
    const ThreadedScene *_scene;
};

}  // namespace rtx::others
