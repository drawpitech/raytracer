/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PpmDisplay
*/

#pragma once

#include <rtx/core/display/IDisplay.hpp>
#include <rtx/core/display/Image.hpp>

#include <shared_mutex>

namespace rtx::display {

class PpmDisplay final : public IDisplay {
   public:
    PpmDisplay(maths::Vector2<std::size_t> resolution) : _image{resolution} {}

    void update(maths::Point2<std::size_t> point, const Image &image) override;

    void write(const std::string &filename);
    void write(std::ostream &os);

   private:
    Image _image;
    std::shared_mutex _image_mutex;
};

}  // namespace rtx::display
