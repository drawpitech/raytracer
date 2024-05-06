/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Image.hpp
*/

#pragma once

#include <vector>
#include <rtx/maths/Point.hpp>
#include <rtx/maths/Vector.hpp>
#include <rtx/core/Types/Color.hpp>

namespace rtx::core {

class Image {
   public:
    explicit Image(maths::Vector2<std::size_t> resolution);

    [[nodiscard]] const maths::Vector2<std::size_t> &resolution() const;
    void setPixel(const maths::Point2<std::size_t> &point, const Color &color);

    [[nodiscard]] const std::vector<Color> &pixels() const;

   private:
    maths::Vector2<std::size_t> _resolution;
    std::vector<Color> _pixels;
};

}  // namespace rtx::core
