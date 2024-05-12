/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PpmDisplay
*/

#include "PpmDisplay.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <mutex>
#include <shared_mutex>

namespace rtx::display {

void PpmDisplay::update(maths::Point2<std::size_t> point, const Image &image) {
    std::shared_lock<std::shared_mutex> lock(_image_mutex);
    _image.setRegion(point, image);
}

void PpmDisplay::startRender(Renderer &renderer) {
    std::clog << "Rendering to " << _filename << "...\n";

    auto start_time = std::chrono::high_resolution_clock::now();
    renderer.startRender();

    std::jthread rt([this](const std::stop_token &stop_token) {
        using namespace std::chrono_literals;

        while (!stop_token.stop_requested()) {
            this->write();
            std::this_thread::sleep_for(100ms);
        }
    });

    renderer.waitRender();
    this->write();

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_time = end_time - start_time;
    std::clog << "Rendering done in " << elapsed_time.count() << "ms\n";
}

void PpmDisplay::write() {
    std::ofstream ofs(_filename);
    std::unique_lock<std::shared_mutex> lock(_image_mutex);

    ofs << "P6\n" << _image.resolution().x() << " " << _image.resolution().y() << "\n255\n";
    for (const auto &pixel : _image.pixels()) {
        ofs << pixel.r() << pixel.g() << pixel.b();
    }
}

}  // namespace rtx::display
