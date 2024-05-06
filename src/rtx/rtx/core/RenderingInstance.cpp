/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RenderingInstance.cpp
*/

#include "RenderingInstance.hpp"

#include "Scene.hpp"

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
            auto ray =
                _viewport.ray({static_cast<double>(i), static_cast<double>(j)});
            std::optional<Hitpoint> hitpoint;
            for (const auto& object : _scene->objects()) {
                const auto tmp = object->hit(ray);
                if (!tmp) {
                    continue;
                }
                if (!hitpoint || tmp->distance() < hitpoint->distance()) {
                    hitpoint = tmp;
                }
            }
            if (hitpoint) {
                _image.setPixel({i, j}, Color::fromNormal(hitpoint->normal()));
            } else {
                _image.setPixel({i, j}, sky(ray.direction().normalized().z()));
            }
        }
    }
}
const Image& RenderingInstance::image() const {
    return _image;
}
// const Image& RenderingInstance::image() const {}
}  // namespace rtx::core
