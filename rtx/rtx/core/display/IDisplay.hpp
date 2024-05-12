/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IDisplay
*/

#pragma once

#include <rtx/core/display/Image.hpp>
#include <rtx/maths/Point.hpp>

#include <cstddef>

namespace rtx::display {

class Renderer;  // forward declaration

/**
 * @brief Interface to update the displayed render. Implementations MUST be
 * thread-safe and should implement a locking mechanism for the `update`
 * method.
 */
class IDisplay {
   public:
    virtual ~IDisplay() = default;

    /**
     * @brief Update the render on the display. This method MUST be thread-safe, but it is safe to
     * assume that the same image region will not be updated by multiple threads simultaneously.
     */
    virtual void update(maths::Point2<std::size_t> point, const Image &image) = 0;

    virtual void startRender(Renderer &renderer) = 0;
};

}  // namespace rtx::display
