/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** main.cpp
*/

#include <rtx/core/config/Config.hpp>
#include <rtx/core/display/PpmDisplay.hpp>
#include <rtx/core/display/SfmlDisplay.hpp>
#include <rtx/core/display/renderer/Renderer.hpp>
#include <rtx/core/scene/Camera.hpp>
#include <rtx/core/scene/Scene.hpp>
#include <rtx/maths/Point.hpp>

#include <iostream>

#include "Args.hpp"

namespace {
int raytracer(const Args &args) {
    using namespace rtx;

    rtx::config::Config config(args.getConfig());
    auto scene = config.parseScene();
    auto camera = config.parseCamera();

    std::unique_ptr<display::IDisplay> display;

    if (args.getDisplay() == "sfml") {
        display = std::make_unique<display::SfmlDisplay>(camera.resolution());
    } else if (args.getDisplay() == "ppm") {
        display = std::make_unique<display::PpmDisplay>(camera.resolution(), args.getOutputFile());
    } else {
        throw std::runtime_error("Unknown display type: " + args.getDisplay());
    }

    display::Renderer renderer{std::move(scene), camera, display.get()};
    display->startRender(renderer);

    return 0;
}
}  // namespace

int main(int argc, char *argv[]) {
    try {
        Args args(argc, argv);
        if (args.getHelp()) {
            args.printHelp();
            return 0;
        }

        return raytracer(args);
    } catch (const std::exception &e) {
        std::cerr << "A fatal error occurred: " << e.what() << "\n";
        return 84;
    }
}
