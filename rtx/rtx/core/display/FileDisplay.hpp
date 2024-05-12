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

class FileDisplay final : public IDisplay {
   public:
    FileDisplay(maths::Vector2<std::size_t> resolution, std::string filename, std::string format)
        : _image{resolution}, _filename{std::move(filename)}, _format{std::move(format)} {}

    void update(maths::Point2<std::size_t> point, const Image &image) override;
    void startRender(Renderer &renderer) override;

   private:
    void write();

    Image _image;
    std::shared_mutex _image_mutex;
    std::string _filename;
    std::string _format;
};

}  // namespace rtx::display
