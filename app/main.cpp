/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** main.cpp
*/

#include <bits/std_thread.h>

#include <fstream>
#include <rtx/render/Camera.hpp>
#include <rtx/render/Primitives/Sphere.hpp>
#include <rtx/core/Types/Color.hpp>
#include <rtx/core/Scene.hpp>
#include <rtx/maths/Matrix.hpp>
#include <rtx/maths/Point.hpp>
#include <rtx/core/Display/PpmBinaryWriter.hpp>

constexpr struct {
    unsigned width;
    unsigned height;
} RESOLUTION{
    .width = 1920,
    .height = 1080,
};

int main(int argc, char *argv[]) {
    rtx::core::Scene scene;
    rtx::basics::Camera camera(
        rtx::maths::Point3{0., 0., 0.},
        rtx::maths::Vector3{0., 0., std::numbers::pi},
        rtx::maths::Vector2<size_t>{1920, 1080}, std::numbers::pi / 2);

    scene.addObject(std::make_unique<rtx::basics::Sphere>(
        rtx::maths::Point3{0., -1., 0.}, 0.5));
    scene.addObject(std::make_unique<rtx::basics::Sphere>(
        rtx::maths::Point3{0., -1., -100.5}, 100));

    auto ri = camera.renderingInstance();

    ri.setScene(scene);

    ri.render();

    // std::thread t(&rtx::core::RenderingInstance::render, &ri);

    // t.join();

    std::ofstream ofs("image.ppm");

    rtx::utils::PpmBinaryWriter{ri.image()}.write(ofs);
}
