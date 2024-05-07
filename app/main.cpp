/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** main.cpp
*/

#include <bits/std_thread.h>

#include <fstream>
#include <rtx/core/Config/Config.hpp>
#include <rtx/core/Display/PpmBinaryWriter.hpp>
#include <rtx/core/Scene.hpp>
#include <rtx/core/Types/Color.hpp>
#include <rtx/maths/Matrix.hpp>
#include <rtx/maths/Point.hpp>
#include <rtx/render/Camera.hpp>
#include <rtx/render/Primitives/Sphere.hpp>

int main(int argc, char *argv[]) {
    rtx::core::Config config;
    config.readFile("scene.cfg");

    auto scene = config.parseScene();
    auto camera = config.parseCamera();

    auto ri = camera.renderingInstance();

    ri.setScene(scene);

    ri.render();

    // std::thread t(&rtx::core::RenderingInstance::render, &ri);

    // t.join();

    std::ofstream ofs("image.ppm");

    rtx::utils::PpmBinaryWriter{ri.image()}.write(ofs);
}
