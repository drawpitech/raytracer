/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Image.hpp
*/

#pragma once

#include <rtx/core/render/Color.hpp>
#include <rtx/maths/Point.hpp>
#include <rtx/maths/Vector.hpp>

#include <vector>

namespace rtx::others {

class Image {
   public:
    explicit Image(maths::Vector2<std::size_t> resolution);

    [[nodiscard]] const maths::Vector2<std::size_t> &resolution() const;
    void setPixel(const maths::Point2<std::size_t> &point, const render::Color &color);

    [[nodiscard]] const std::vector<render::Color> &pixels() const;

   private:
    maths::Vector2<std::size_t> _resolution;
    std::vector<render::Color> _pixels;
};

}  // namespace rtx::others
