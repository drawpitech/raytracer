/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** FileDisplay
*/

#include "FileDisplay.hpp"

#include <chrono>
#include <iostream>
#include <mutex>
#include <shared_mutex>

namespace rtx::display {

void FileDisplay::update(maths::Point2<std::size_t> point, const Image &image) {
    std::shared_lock<std::shared_mutex> lock(_image_mutex);
    _image.setRegion(point, image);
}

void FileDisplay::startRender(Renderer &renderer) {
    std::clog << "Rendering to " << _filename << "...\n";

    auto start_time = std::chrono::high_resolution_clock::now();
    renderer.startRender();

    std::jthread rt([this](const std::stop_token &stop_token) {
        using namespace std::chrono_literals;

        while (!stop_token.stop_requested()) {
            _image.writeToFile(_filename, _format);
            std::this_thread::sleep_for(100ms);
        }
    });

    renderer.waitRender();
    _image.writeToFile(_filename, _format);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_time = end_time - start_time;
    std::clog << "Rendering done in " << elapsed_time.count() << "ms\n";
}

void FileDisplay::write() {
    std::unique_lock<std::shared_mutex> lock(_image_mutex);
    _image.writeToFile(_filename, _format);
}

}  // namespace rtx::display
