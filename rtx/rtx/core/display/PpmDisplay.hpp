/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PpmDisplay
*/

#pragma once

#include <rtx/core/display/IDisplay.hpp>
#include <rtx/core/display/Image.hpp>
#include <rtx/core/display/renderer/Renderer.hpp>

#include <shared_mutex>

namespace rtx::display {

class PpmDisplay final : public IDisplay {
   public:
    PpmDisplay(maths::Vector2<std::size_t> resolution, std::string filename)
        : _image{resolution}, _filename{std::move(filename)} {}

    void update(maths::Point2<std::size_t> point, const Image &image) override;
    void startRender(Renderer &renderer) override;

   private:
    void write();

    Image _image;
    std::shared_mutex _image_mutex;
    std::string _filename;
};

}  // namespace rtx::display
