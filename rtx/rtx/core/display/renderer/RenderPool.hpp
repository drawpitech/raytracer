/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RenderPool
*/

#pragma once

#include <rtx/core/display/IDisplay.hpp>
#include <rtx/core/scene/Scene.hpp>
#include <rtx/core/scene/Viewport.hpp>
#include <rtx/maths/Rectangle.hpp>
#include <rtx/maths/Vector.hpp>

#include <queue>
#include <stop_token>
#include <thread>
#include <vector>

namespace rtx::display {

/**
 * @brief Handles the thread pool for the scene rendering. This class can only
 * be used once, it must be re-initialized for each new render.
 */
class RenderPool {
   public:
    RenderPool(
        scene::SceneRef scene,
        const scene::Viewport &viewport,
        const maths::Vector2<size_t> &resolution,
        IDisplay *display,
        unsigned int thread_count
    )
        : _scene{std::move(scene)},
          _viewport{viewport},
          _resolution{resolution},
          _display{display},
          _thread_count{thread_count} {}

    void render(maths::Vector2<size_t> cluster_size);
    void cancel();
    void join();

    [[nodiscard]] bool isRunning() const;

   private:
    void generateClusters(const maths::Vector2<size_t> &cluster_size);
    void renderThread(const std::stop_token &stop_token);
    void renderCluster(const std::stop_token &stop_token, maths::Rectangle2<size_t> rect);

    scene::SceneRef _scene;
    scene::Viewport _viewport;
    maths::Vector2<size_t> _resolution;
    IDisplay *_display;

    unsigned int _thread_count;
    std::vector<std::jthread> _threads;
    std::queue<maths::Rectangle2<size_t>> _queue;
    std::mutex _queue_mutex;
};

}  // namespace rtx::display
