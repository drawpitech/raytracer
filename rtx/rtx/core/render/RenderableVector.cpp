/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RenderableVector.cpp
*/

#include "RenderableVector.hpp"

namespace rtx::render {
std::optional<Hitpoint> RenderableVector::hit(const maths::Ray3<double> &ray) const {
    std::optional<Hitpoint> hitpoint;
    for (const auto &object : *this) {
        const auto hit = object->hit(ray);
        if (!hit || hit->distance() < 0 || (hitpoint && hit->distance() > hitpoint->distance())) {
            continue;
        }
        hitpoint = hit;
    }
    return hitpoint;
}

std::optional<Hitpoint>
RenderableVector::hit_ignore(const maths::Ray3<double> &ray, const IRenderable &ignore) const {
    std::optional<Hitpoint> hitpoint;
    for (const auto &object : *this) {
        if (object == &ignore) {
            continue;
        }
        const auto hit = object->hit(ray);
        if (!hit || hit->distance() < 0 || (hitpoint && hit->distance() > hitpoint->distance())) {
            continue;
        }
        hitpoint = hit;
    }
    return hitpoint;
}
}  // namespace rtx::render
