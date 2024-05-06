/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RenderingInstance.cpp
*/

#include <rtx/core/Scene.hpp>

#include "RayRender.hpp"
#include "RenderingInstance.hpp"

namespace rtx::core {

RenderingInstance::RenderingInstance(
    const basics::Viewport& viewport, const maths::Vector2<size_t> resolution)
    : _resolution{resolution}, _viewport{viewport}, _image{resolution} {}

void RenderingInstance::setScene(const Scene& scene) {
    _scene = &scene;
}

void RenderingInstance::render() {
    for (size_t i = 0; i < _resolution.x(); i++) {
        for (size_t j = 0; j < _resolution.y(); j++) {
            auto ray = _viewport.ray({static_cast<double>(i), static_cast<double>(j)});
            _image.setPixel({i, j}, render::RayRender{ray, *_scene}.render());
        }
    }
}

const Image& RenderingInstance::image() const {
    return _image;
}

}  // namespace rtx::core
