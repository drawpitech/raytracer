/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Image.cpp
*/

#include "Image.hpp"

#include <cstdint>
#include <cstring>

namespace rtx::display {

Image::Image(maths::Vector2<std::size_t> resolution) : _resolution{resolution} {
    _pixels.resize(resolution.x() * resolution.y());
}

void Image::setPixel(maths::Point2<std::size_t> point, Pixel pixel) {
    this->at(point) = pixel;
}

void Image::setRegion(maths::Point2<std::size_t> point, const Image &image) {
    for (size_t j = 0; j < image.resolution().y(); j++) {
        auto src = &image.at({0, j});
        auto dest = &this->at({point.x(), point.y() + j});

        std::memcpy(dest, src, image.resolution().x() * sizeof(Pixel));
    }
}

void Image::clear(maths::Vector2<std::size_t> resolution) {
    _pixels.clear();
    _pixels.resize(resolution.x() * resolution.y());
}

Pixel &Image::at(maths::Point2<std::size_t> point) {
    return _pixels.at(point.x() + point.y() * _resolution.x());
}

const Pixel &Image::at(maths::Point2<std::size_t> point) const {
    return _pixels.at(point.x() + point.y() * _resolution.x());
}

const std::vector<Pixel> &Image::pixels() const {
    return _pixels;
}

const maths::Vector2<std::size_t> &Image::resolution() const {
    return _resolution;
}

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : _value{static_cast<uint32_t>((r << 24) | (g << 16) | (b << 8) | a)} {}

Pixel::Pixel(const render::Color &color) {
    auto r = static_cast<uint32_t>(color.r() * 255.999);
    auto g = static_cast<uint32_t>(color.g() * 255.999);
    auto b = static_cast<uint32_t>(color.b() * 255.999);
    _value = (r << 24) | (g << 16) | (b << 8) | 255;
}

uint32_t Pixel::value() const {
    return _value;
}

uint8_t Pixel::r() const {
    return static_cast<uint8_t>(_value >> 24);
}

uint8_t Pixel::g() const {
    return static_cast<uint8_t>((_value >> 16) & 0xFF);
}

uint8_t Pixel::b() const {
    return static_cast<uint8_t>((_value >> 8) & 0xFF);
}

uint8_t Pixel::a() const {
    return static_cast<uint8_t>(_value & 0xFF);
}

}  // namespace rtx::display
