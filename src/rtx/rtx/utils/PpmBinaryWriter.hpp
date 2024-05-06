/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** PpmBinaryWriter.hpp
*/

#pragma once

#include <utility>

#include "ImageWriter.hpp"

namespace rtx::utils {

class PpmBinaryWriter : public IImageWriter {
   public:
    explicit PpmBinaryWriter(core::Image image) : _image{std::move(image)} {}
    void write(std::ostream &os) const override;

   private:
    core::Image _image;
};

}  // namespace rtx::utils
