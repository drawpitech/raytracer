/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RayRender.cpp
*/

#include "RenderPixel.hpp"

#include <rtx/maths/Random.hpp>

#include "Materials.hpp"

namespace rtx::render {

Color RenderPixel::render(maths::Point2<size_t> point) const {
    maths::Point2 dpoint{static_cast<double>(point.x()), static_cast<double>(point.y())};
    Color color = renderRay(_viewport.ray({dpoint.x() + 0.5, dpoint.y() + 0.5}));
    for (unsigned i = 1; i < _scene->config().samples; i++) {
        const double x = maths::Random::randomDouble(0., 1.);
        const double y = maths::Random::randomDouble(0., 1.);
        color = color + renderRay(_viewport.ray({dpoint.x() + x, dpoint.y() + y}));
    }
    return color / _scene->config().samples;
}

Color RenderPixel::renderRay(const maths::Ray3<double> &ray) const {
    if (const std::optional<Hitpoint> hitpoint = _scene->objects().hit(ray)) {
        return hitpoint->object().material().render(*hitpoint, *_scene);
    }
    return Color::sky(ray.direction().normalized().z());
}
}  // namespace rtx::render
