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
    double t = std::numeric_limits<double>::infinity();
    for (const auto &object : *this) {
        const auto hit = object->hit(ray);
        if (!hit) {
            continue;
        }
        const auto distance = hit->distance();
        if (distance > 0.0001 && (!hitpoint || distance < t)) {
            hitpoint = hit;
            t = hit->distance();
        }
    }
    return hitpoint;
}

std::optional<Hitpoint>
RenderableVector::hit(const maths::Ray3<double> &ray, const IRenderable &ignore) const {
    std::optional<Hitpoint> hitpoint;
    double t = std::numeric_limits<double>::infinity();
    for (const auto &object : *this) {
        if (object == &ignore) {
            continue;
        }
        const auto hit = object->hit(ray);
        if (!hit) {
            continue;
        }
        const auto distance = hit->distance();
        if (distance > 0 && (!hitpoint || distance < t)) {
            hitpoint = hit;
            t = hit->distance();
        }
    }
    return hitpoint;
}
}  // namespace rtx::render
