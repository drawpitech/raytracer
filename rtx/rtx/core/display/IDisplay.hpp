/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IDisplay
*/

#pragma once

#include <rtx/core/display/Image.hpp>

#include <cstddef>

#include "rtx/maths/Point.hpp"

namespace rtx::display {

/**
 * @brief Interface to update the displayed render. Implementations MUST be
 * thread-safe and should implement a locking mechanism for the `update`
 * method.
 */
class IDisplay {
   public:
    virtual ~IDisplay() = default;
    virtual void update(maths::Point2<std::size_t> point, const Image &image) = 0;
};

}  // namespace rtx::display
