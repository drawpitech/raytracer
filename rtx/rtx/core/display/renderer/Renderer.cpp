/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Renderer
*/

#include "Renderer.hpp"

namespace rtx::display {

void Renderer::startRender(maths::Vector2<size_t> cluster_size, unsigned int thread_count) {
    if (_render_pool.has_value() && _render_pool->isRunning()) {
        _render_pool->cancel();
    }

    _render_pool.emplace(
        _scene.asRef(), _camera.viewport(), _camera.resolution(), _display, thread_count
    );
    _render_pool->render(cluster_size);
}

void Renderer::cancelRender() {
    if (_render_pool.has_value()) {
        _render_pool->cancel();
    }
}

void Renderer::waitRender() {
    if (_render_pool.has_value() && _render_pool->isRunning()) {
        _render_pool->join();
    }
}

}  // namespace rtx::display
