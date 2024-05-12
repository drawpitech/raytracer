/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RenderPool
*/

#include "RenderPool.hpp"

#include <rtx/core/display/Image.hpp>
#include <rtx/core/render/RenderPixel.hpp>
#include <rtx/maths/Vector.hpp>

#include <mutex>

namespace rtx::display {

void RenderPool::render(maths::Vector2<size_t> cluster_size) {
    if (isRunning()) {
        throw std::runtime_error("RenderPool is already running, please initialize a new one");
    }

    generateClusters(cluster_size);
    for (unsigned int i = 0; i < _thread_count; i++) {
        _threads.emplace_back(&RenderPool::renderThread, this);
    }
}

bool RenderPool::isRunning() const {
    return !_threads.empty();
}

void RenderPool::cancel() {
    for (auto &thread : _threads) {
        thread.request_stop();
    }
    join();
}

void RenderPool::join() {
    for (auto &thread : _threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void RenderPool::generateClusters(const maths::Vector2<size_t> &cluster_size) {
    for (size_t j = 0; j < _resolution.y(); j += cluster_size.y()) {
        for (size_t i = 0; i < _resolution.x(); i += cluster_size.x()) {
            maths::Point2<size_t> point{i, j};
            maths::Vector2<size_t> size{
                std::min(cluster_size.x(), _resolution.x() - i),
                std::min(cluster_size.y(), _resolution.y() - j)
            };

            _queue.emplace(point, size);
        }
    }
}

void RenderPool::renderThread(const std::stop_token &stop_token) {
    while (!stop_token.stop_requested()) {
        maths::Rectangle2<size_t> rect = {{0, 0}, {0, 0}};

        {  // Scope to ensure the lock is released
            std::unique_lock<std::mutex> lock(_queue_mutex);
            if (_queue.empty()) {
                return;
            }
            rect = _queue.front();
            _queue.pop();
        }

        renderCluster(stop_token, rect);
    }
}

void RenderPool::renderCluster(const std::stop_token &stop_token, maths::Rectangle2<size_t> rect) {
    Image image{{rect.size().x(), 1}};  // render on row at the same time

    for (size_t j = 0; j < rect.size().y(); j++) {
        for (size_t i = 0; i < rect.size().x(); i++) {
            maths::Point2<size_t> target{i + rect.point().x(), j + rect.point().y()};
            auto color = render::RenderPixel{_scene, _viewport}.render(target);

            image.setPixel({i, 0}, color);
        }

        _display->update({rect.point().x(), rect.point().y() + j}, image);
        if (stop_token.stop_requested()) {
            return;
        }
    }
}

}  // namespace rtx::display
