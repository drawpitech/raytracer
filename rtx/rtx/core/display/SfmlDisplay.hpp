/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SfmlDisplay
*/

#pragma once

#include <rtx/core/display/IDisplay.hpp>
#include <rtx/core/display/renderer/Renderer.hpp>

#include <SFML/Graphics.hpp>

namespace rtx::display {

class SfmlDisplay final : public IDisplay {
   public:
    SfmlDisplay(maths::Vector2<std::size_t> resolution);

    void update(maths::Point2<std::size_t> point, const Image &image) override;
    void startRender(Renderer &renderer) override;

   private:
    void _sfmlHandleEvent(const sf::Event &event, Renderer &renderer);

    sf::RenderWindow _window;
    sf::Texture _texture;
    sf::Sprite _texture_sprite;
};

}  // namespace rtx::display
