/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SfmlDisplay
*/

#include "SfmlDisplay.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdint>
#include <functional>

namespace rtx::display {

SfmlDisplay::SfmlDisplay(maths::Vector2<std::size_t> resolution) {
    auto width = static_cast<unsigned int>(resolution.x());
    auto height = static_cast<unsigned int>(resolution.y());

    _window.create({width, height}, "Raytracer", sf::Style::Close | sf::Style::Titlebar);
    _window.setFramerateLimit(30);

    _texture.create(width, height);
    _texture_sprite.setTexture(_texture, true);
}

void SfmlDisplay::update(maths::Point2<std::size_t> point, const Image &image) {
    auto *pixels = reinterpret_cast<const uint8_t *>(image.pixels().data());
    auto x = static_cast<unsigned int>(point.x());
    auto y = static_cast<unsigned int>(point.y());
    auto width = static_cast<unsigned int>(image.resolution().x());
    auto height = static_cast<unsigned int>(image.resolution().y());

    _texture.update(pixels, width, height, x, y);
}

void SfmlDisplay::startRender(Renderer &renderer) {
    renderer.startRender();

    while (_window.isOpen()) {
        sf::Event event{};
        while (_window.pollEvent(event)) {
            _sfmlHandleEvent(event, renderer);
        }

        _window.clear();
        _window.draw(_texture_sprite);
        _window.display();
    }
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
