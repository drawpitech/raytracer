/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RenderingInstance.cpp
*/

#include "RenderInstance.hpp"

#include "Scene.hpp"
#include "Viewport.hpp"

namespace rtx::others {
RenderInstance::RenderInstance(
    const ThreadedScene &scene,
    const Viewport &viewport,
    const maths::Vector2<std::size_t> resolution
)
    : _scene{&scene}, _resolution{resolution}, _viewport{viewport}, _image{resolution} {}

RenderCluster RenderInstance::renderCluster(
    const maths::Point2<size_t> topleft,
    const maths::Vector2<size_t> bottomright
) {
    return RenderCluster{{topleft, bottomright}, _image, _viewport, *_scene};
}

const Image &RenderInstance::image() const {
    return _image;
}

// const Image& RenderingInstance::image() const {}
}  // namespace rtx::others
