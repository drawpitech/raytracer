/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Image.hpp
*/

#pragma once

#include <rtx/core/render/Color.hpp>
#include <rtx/maths/Point.hpp>
#include <rtx/maths/Rectangle.hpp>
#include <rtx/maths/Vector.hpp>

#include <cstdint>
#include <vector>

namespace rtx::display {

class Pixel final {
   public:
    Pixel() = default;

    Pixel(std::uint32_t value) : _value{value} {}

    Pixel(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255);
    Pixel(const render::Color &color);

    [[nodiscard]] uint32_t value() const;

    [[nodiscard]] uint8_t r() const;
    [[nodiscard]] uint8_t g() const;
    [[nodiscard]] uint8_t b() const;
    [[nodiscard]] uint8_t a() const;

   private:
    std::uint32_t _value;
};

class Image final {
   public:
    explicit Image(maths::Vector2<std::size_t> resolution);

    void setPixel(maths::Point2<std::size_t> point, Pixel pixel);
    void setRegion(maths::Point2<std::size_t> point, const Image &image);
    void clear(maths::Vector2<std::size_t> resolution);

    Pixel &at(maths::Point2<std::size_t> point);
    [[nodiscard]] const Pixel &at(maths::Point2<std::size_t> point) const;

    [[nodiscard]] const std::vector<Pixel> &pixels() const;
    [[nodiscard]] const maths::Vector2<std::size_t> &resolution() const;

   private:
    maths::Vector2<std::size_t> _resolution;
    std::vector<Pixel> _pixels;
};

}  // namespace rtx::display
