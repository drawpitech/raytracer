/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Renderer
*/

#pragma once

#include <rtx/core/display/IDisplay.hpp>
#include <rtx/core/display/renderer/RenderPool.hpp>
#include <rtx/core/scene/Camera.hpp>
#include <rtx/core/scene/Scene.hpp>

namespace rtx::display {

/**
 * @brief Schedules the rendering of the scene.
 *
 * SAFETY: This class holds the `scene` instance, which is shared with the
 * rendering threads during the rendering process. Modifications to the scene
 * instance are only allowed when no rendering thread is running.
 */
class Renderer final {
   public:
    Renderer(scene::Scene scene, scene::Camera camera, IDisplay *display)
        : _scene{std::move(scene)}, _camera{camera}, _display{display} {}

    void startRender(
        maths::Vector2<size_t> cluster_size = {200, 200},
        unsigned int thread_count = std::jthread::hardware_concurrency()
    );
    void cancelRender();
    void waitRender();

   private:
    scene::Scene _scene;
    scene::Camera _camera;
    IDisplay *_display;

    std::optional<RenderPool> _render_pool = std::nullopt;
};

}  // namespace rtx::display
