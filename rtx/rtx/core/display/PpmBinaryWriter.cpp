/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** PpmBinaryWriter.cpp
*/

#include "PpmBinaryWriter.hpp"

namespace rtx::display {

void PpmBinaryWriter::write(std::ostream &os) const {
    os << "P6\n" << _image.resolution().x() << " " << _image.resolution().y() << "\n255\n";
    for (const auto &pixel : _image.pixels()) {
        os << static_cast<u_int8_t>(sqrt(pixel.r()) * 255)
           << static_cast<u_int8_t>(sqrt(pixel.g()) * 255)
           << static_cast<u_int8_t>(sqrt(pixel.b()) * 255);
    }
}

}  // namespace rtx::display
