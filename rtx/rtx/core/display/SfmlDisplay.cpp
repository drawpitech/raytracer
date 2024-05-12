/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SfmlDisplay
*/

#include "SfmlDisplay.hpp"

#include <rtx/core/config/Config.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <functional>
#include <iostream>
#include <mutex>

namespace rtx::display {

SfmlDisplay::SfmlDisplay(
    maths::Vector2<std::size_t> resolution,
    std::string config_file,
    std::string output_file,
    std::string format
)
    : _config_file{std::move(config_file)},
      _output_file{std::move(output_file)},
      _format{std::move(format)},
      _image{resolution} {
    auto width = static_cast<unsigned int>(resolution.x());
    auto height = static_cast<unsigned int>(resolution.y());

    _window.create({width, height}, "Raytracer", sf::Style::Close | sf::Style::Titlebar);
    _window.setFramerateLimit(30);

    _texture.create(width, height);
    _texture_sprite.setTexture(_texture, true);

    _config_last_modified = std::filesystem::last_write_time(_config_file);
}

void SfmlDisplay::update(maths::Point2<std::size_t> point, const Image &image) {
    std::shared_lock<std::shared_mutex> lock(_image_mutex);

    auto *pixels = reinterpret_cast<const uint8_t *>(image.pixels().data());
    auto x = static_cast<unsigned int>(point.x());
    auto y = static_cast<unsigned int>(point.y());
    auto width = static_cast<unsigned int>(image.resolution().x());
    auto height = static_cast<unsigned int>(image.resolution().y());

    _texture.update(pixels, width, height, x, y);
    _image.setRegion({point.x(), point.y()}, image);
}

void SfmlDisplay::startRender(Renderer &renderer) {
    renderer.startRender();

    while (_window.isOpen()) {
        sf::Event event{};
        while (_window.pollEvent(event)) {
            _sfmlHandleEvent(event, renderer);
        }

        _reloadConfig(renderer);

        _window.clear();
        _window.draw(_texture_sprite);
        _window.display();
    }
}

void SfmlDisplay::_reloadConfig(Renderer &renderer) {
    if (!std::filesystem::exists(_config_file)) {
        return;
    }

    auto modified_time = std::filesystem::last_write_time(_config_file);
    if (modified_time != _config_last_modified) {
        _config_last_modified = modified_time;

        auto config = config::Config(_config_file.string());
        auto scene = config.parseScene();
        auto camera = config.parseCamera();

        renderer.cancelRender();
        renderer.scene() = std::move(scene);
        renderer.camera() = camera;
        renderer.startRender();
    }
}

void SfmlDisplay::_writeImage() {
    _image_thread = std::jthread([this]() {
        std::unique_lock<std::shared_mutex> lock(_image_mutex);
        if (_image.writeToFile(_output_file, _format)) {
            std::clog << "Image written to " << _output_file << "\n";
        }
    });
}

namespace {
void updateCamera(Renderer &renderer, const std::function<void(scene::Camera &)> &update) {
    renderer.cancelRender();
    update(renderer.camera());
    renderer.startRender();
}
}  // namespace

void SfmlDisplay::_sfmlHandleEvent(const sf::Event &event, Renderer &renderer) {
    if (event.type == sf::Event::Closed) {
        _window.close();
    }

    if (event.type == sf::Event::KeyPressed) {
        auto key = event.key.code;

        if (key == sf::Keyboard::Escape) {
            _window.close();
        }
        if (key == sf::Keyboard::Space) {
            _writeImage();
        }

        // Arrow keys
        if (key == sf::Keyboard::Left) {
            updateCamera(renderer, [](scene::Camera &camera) { camera.angle().x() += 0.05; });
        }
        if (key == sf::Keyboard::Right) {
            updateCamera(renderer, [](scene::Camera &camera) { camera.angle().x() -= 0.05; });
        }
        if (key == sf::Keyboard::Up) {
            updateCamera(renderer, [](scene::Camera &camera) { camera.angle().y() += 0.05; });
        }
        if (key == sf::Keyboard::Down) {
            updateCamera(renderer, [](scene::Camera &camera) { camera.angle().y() -= 0.05; });
        }
    }
}

}  // namespace rtx::display
