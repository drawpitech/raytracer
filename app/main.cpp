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

#include "Args.hpp"

namespace {
void raytracer(const std::string &config_file) {
    rtx::config::Config config(config_file);
    auto scene = config.parseScene();
    auto camera = config.parseCamera();

    rtx::display::PpmDisplay display{camera.resolution()};
    rtx::display::Renderer renderer{std::move(scene), camera, &display};

    std::cout << "Rendering ..."
              << "\n";
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
        Args args(argc, argv);
        if (args.getHelp()) {
            args.printHelp();
            return 0;
        }
        raytracer(args.getConfig());
    } catch (const std::exception &e) {
        std::cerr << "A fatal error occurred: " << e.what() << "\n";
        return 84;
    }
}
