/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RayRender.cpp
*/

#include "RenderPixel.hpp"

#include <rtx/maths/Random.hpp>

#include "Material.hpp"

namespace rtx::render {

Color RenderPixel::render(maths::Point2<size_t> point) const {
    maths::Point2 dpoint{static_cast<double>(point.x()), static_cast<double>(point.y())};
    const auto &config = std::get<scene::settings::FastRenderConfig>(_scene->config());

    switch (config.antialiasing) {
        case scene::settings::Antialiasing::NONE:
            return renderRay(_viewport.ray({dpoint.x() + 0.5, dpoint.y() + 0.5}));
        case scene::settings::Antialiasing::MSAA_X4:
            return (renderRay(_viewport.ray({dpoint.x() + 0.2, dpoint.y() + 0.6})) +
                    renderRay(_viewport.ray({dpoint.x() + 0.4, dpoint.y() + 0.2})) +
                    renderRay(_viewport.ray({dpoint.x() + 0.8, dpoint.y() + 0.6})) +
                    renderRay(_viewport.ray({dpoint.x() + 0.4, dpoint.y() + 0.8}))) /
                   4;
        default:
            throw std::runtime_error("Unknown antialiasing mode");
    }
}

Color RenderPixel::renderRay(const maths::Ray3<double> &ray) const {
    if (const std::optional<Hitpoint> hitpoint = _scene->objects().hit(ray)) {
        return hitpoint->object().material().render(*hitpoint, *_scene);
    }
    return Color::sky(ray.direction().normalized().z());
}
}  // namespace rtx::render
