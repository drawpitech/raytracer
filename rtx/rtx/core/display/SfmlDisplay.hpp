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
#include <filesystem>
#include <shared_mutex>

namespace rtx::display {

class SfmlDisplay final : public IDisplay {
   public:
    SfmlDisplay(
        maths::Vector2<std::size_t> resolution,
        std::string config_file,
        std::string output_file,
        std::string format
    );

    void update(maths::Point2<std::size_t> point, const Image &image) override;
    void startRender(Renderer &renderer) override;

   private:
    void _sfmlHandleEvent(const sf::Event &event, Renderer &renderer);
    void _reloadConfig(Renderer &renderer);
    void _writeImage();

    std::filesystem::path _config_file;
    std::filesystem::file_time_type _config_last_modified;

    std::string _output_file;
    std::string _format;

    Image _image;
    std::shared_mutex _image_mutex;
    std::jthread _image_thread;

    sf::RenderWindow _window;
    sf::Texture _texture;
    sf::Sprite _texture_sprite;
};

}  // namespace rtx::display
