/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Image.cpp
*/

#include "Image.hpp"

namespace rtx::others {

Image::Image(maths::Vector2<std::size_t> resolution) : _resolution{resolution} {
    _pixels.resize(resolution.x() * resolution.y());
}

const maths::Vector2<std::size_t> &Image::resolution() const {
    return _resolution;
}

void Image::setPixel(const maths::Point2<std::size_t> &point, const render::Color &color) {
    _pixels.at(point.x() + point.y() * _resolution.x()) = color;
}

const std::vector<render::Color> &Image::pixels() const {
    return _pixels;
}
}  // namespace rtx::others
