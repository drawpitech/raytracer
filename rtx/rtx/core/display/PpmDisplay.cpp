/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PpmDisplay
*/

#include "PpmDisplay.hpp"

#include <fstream>
#include <mutex>
#include <shared_mutex>

namespace rtx::display {

void PpmDisplay::update(maths::Point2<std::size_t> point, const Image &image) {
    std::shared_lock<std::shared_mutex> lock(_image_mutex);
    _image.setRegion(point, image);
}

void PpmDisplay::write(const std::string &filename) {
    std::ofstream ofs(filename);
    write(ofs);
}

void PpmDisplay::write(std::ostream &os) {
    std::unique_lock<std::shared_mutex> lock(_image_mutex);

    os << "P6\n" << _image.resolution().x() << " " << _image.resolution().y() << "\n255\n";
    for (const auto &pixel : _image.pixels()) {
        os << pixel.r() << pixel.g() << pixel.b();
    }
}

}  // namespace rtx::display
