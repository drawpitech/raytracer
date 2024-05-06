/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RayRender.cpp
*/

#include "RayRender.hpp"

namespace rtx::render {

core::Color RayRender::render() const {
    std::optional<core::Hitpoint> hitpoint;
    for (const auto& object : _scene->objects()) {
        const auto tmp = object->hit(_ray);
        if (!tmp) {
            continue;
        }
        if (!hitpoint || tmp->distance() < hitpoint->distance()) {
            hitpoint = tmp;
        }
    }
    if (hitpoint) {
        return core::Color::fromNormal(hitpoint->normal());
    } else {
        core::Color::sky(_ray.direction().normalized().z());
    }
}
}  // namespace rtx::render
