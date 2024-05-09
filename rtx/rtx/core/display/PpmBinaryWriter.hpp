/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** PpmBinaryWriter.hpp
*/

#pragma once

#include <rtx/core/others/Image.hpp>

#include <utility>

#include "ImageWriter.hpp"

namespace rtx::display {

class PpmBinaryWriter : public IImageWriter {
   public:
    explicit PpmBinaryWriter(others::Image image) : _image{std::move(image)} {}

    void write(std::ostream &os) const override;

   private:
    others::Image _image;
};

}  // namespace rtx::display
