/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ImageWriter.hpp
*/

#pragma once

#include <ostream>

namespace rtx::display {

class IImageWriter {
   public:
    IImageWriter() = default;
    virtual ~IImageWriter() = default;

    IImageWriter(const IImageWriter &) = delete;
    IImageWriter(IImageWriter &&) = default;

    IImageWriter &operator=(const IImageWriter &) = delete;
    IImageWriter &operator=(IImageWriter &&) = default;

    virtual void write(std::ostream &os) const = 0;
};
}  // namespace rtx::display
