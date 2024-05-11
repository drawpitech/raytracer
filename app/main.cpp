/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** main.cpp
*/

#include <rtx/core/config/Config.hpp>
#include <rtx/core/display/PpmBinaryWriter.hpp>
#include <rtx/core/others/Camera.hpp>
#include <rtx/core/others/Scene.hpp>
#include <rtx/maths/Point.hpp>

#include <fstream>
#include <iostream>
#include <thread>

void realtime(const rtx::others::RenderInstance &ri, std::atomic_bool &cancel) {
    while (!cancel) {
        std::ofstream ofs("image.ppm");

        rtx::display::PpmBinaryWriter{ri.image()}.write(ofs);

        ofs.close();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::ofstream ofs("image.ppm");

    rtx::display::PpmBinaryWriter{ri.image()}.write(ofs);
}

int main(int argc, char *argv[]) {
    rtx::config::Config config;

    std::optional<rtx::others::Scene> scene;
    std::optional<rtx::others::Camera> camera;

    try {
        config.readFile("scene.cfg");
        scene = config.parseScene();
        camera = config.parseCamera();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    auto scene2 = scene.value().threadedScene();

    auto ri = camera.value().renderingInstance(scene2);

    std::atomic_bool cancel = false;

    auto cluster1 = ri.renderCluster({0, 0}, {600, 600});
    auto cluster2 = ri.renderCluster({600, 0}, {600, 600});
    auto cluster3 = ri.renderCluster({1200, 0}, {600, 600});
    auto cluster4 = ri.renderCluster({0, 600}, {600, 600});
    auto cluster5 = ri.renderCluster({600, 600}, {600, 600});
    auto cluster6 = ri.renderCluster({1200, 600}, {600, 600});

    std::thread t1(&rtx::others::RenderCluster::render, &cluster1);
    std::thread t2(&rtx::others::RenderCluster::render, &cluster2);
    std::thread t3(&rtx::others::RenderCluster::render, &cluster3);
    std::thread t4(&rtx::others::RenderCluster::render, &cluster4);
    std::thread t5(&rtx::others::RenderCluster::render, &cluster5);
    std::thread t6(&rtx::others::RenderCluster::render, &cluster6);

    std::thread rt(&realtime, std::ref(ri), std::ref(cancel));

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();

    cancel = true;

    rt.join();
}
