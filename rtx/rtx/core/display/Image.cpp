/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Image.cpp
*/

#include "Image.hpp"

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>

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

bool Image::writeToFile(const std::string &filename, const std::string &format) {
    if (format == "ppm") {
        return _writePpm(filename);
    } else if (format == "png" || format == "jpg" || format == "bmp") {
        return _writeSfml(filename, format);
    } else {
        std::clog << "Failed to write, unsupported image format: " << format << "\n";
        return false;
    }
}

bool Image::_writePpm(const std::string &filename) {
    std::ofstream ofs(filename);

    ofs << "P6\n" << _resolution.x() << " " << _resolution.y() << "\n255\n";
    for (const auto &pixel : _pixels) {
        ofs << pixel.r() << pixel.g() << pixel.b();
    }

    return true;
}

bool Image::_writeSfml(const std::string &filename, const std::string &format) {
    std::clog << "SFML from Epitech doesn't support writing images :(\n";
    return false;

    // sf::Image image = sf::Image();
    // std::vector<uint8_t> buffer;

    // auto *pixels = reinterpret_cast<const uint8_t *>(_pixels.data());
    // image.create(_resolution.x(), _resolution.y(), pixels);
    // image.saveToMemory(buffer, format);

    // std::ofstream ofs(filename, std::ios::binary);
    // ofs.write(reinterpret_cast<const char *>(buffer.data()), buffer.size());
    // return true;
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

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : _value{{r, g, b, a}} {}

Pixel::Pixel(const render::Color &color) : _value() {
    auto r = static_cast<uint8_t>(color.r() * 255.999);
    auto g = static_cast<uint8_t>(color.g() * 255.999);
    auto b = static_cast<uint8_t>(color.b() * 255.999);
    _value = {r, g, b, std::numeric_limits<uint8_t>::max()};
}

std::array<std::uint8_t, 4> Pixel::value() const {
    return _value;
}

uint8_t Pixel::r() const {
    return _value[0];
}

uint8_t Pixel::g() const {
    return _value[1];
}

uint8_t Pixel::b() const {
    return _value[2];
}

uint8_t Pixel::a() const {
    return _value[3];
}

}  // namespace rtx::display
