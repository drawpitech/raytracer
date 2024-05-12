/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** main.cpp
*/

#include <rtx/core/config/Config.hpp>
#include <rtx/core/display/PpmDisplay.hpp>
#include <rtx/core/display/renderer/Renderer.hpp>
#include <rtx/core/scene/Camera.hpp>
#include <rtx/core/scene/Scene.hpp>
#include <rtx/maths/Point.hpp>

#include <iostream>

namespace {
void raytracer() {
    rtx::config::Config config("scene.cfg");
    auto scene = config.parseScene();
    auto camera = config.parseCamera();

    rtx::display::PpmDisplay display{camera.resolution()};
    rtx::display::Renderer renderer{std::move(scene), camera, &display};

    std::cout << "Rendering ..." << std::endl;
    renderer.startRender();

    std::jthread rt([&display](const std::stop_token &stop_token) {
        using namespace std::chrono_literals;

        while (!stop_token.stop_requested()) {
            display.write("image.ppm");
            std::this_thread::sleep_for(100ms);
        }
    });

    renderer.waitRender();
    display.write("image.ppm");
}
}  // namespace

int main(int argc, char *argv[]) {
    try {
        raytracer();
    } catch (const std::exception &e) {
        std::cerr << "A fatal error occurred: " << e.what() << std::endl;
        return 84;
    }
}
