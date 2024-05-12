/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Camera.hpp
*/

#pragma once

#include <rtx/maths/Rectangle.hpp>

#include "Viewport.hpp"

namespace rtx::scene {

class Camera {
   public:
    Camera(
        maths::Point3<double> position,
        maths::Vector3<double> angle,
        maths::Vector2<std::size_t> resolution,
        double fov
    )
        : _position{position}, _angle{angle}, _resolution{resolution}, _fov{fov} {}

    Viewport viewport();
    Viewport viewport(maths::Rectangle2<std::size_t> rect);

    maths::Point3<double> &position();
    [[nodiscard]] const maths::Point3<double> &position() const;

    maths::Vector3<double> &angle();
    [[nodiscard]] const maths::Vector3<double> &angle() const;

    maths::Vector2<size_t> &resolution();
    [[nodiscard]] const maths::Vector2<size_t> &resolution() const;

    double &fov();
    [[nodiscard]] const double &fov() const;

   private:
    maths::Point3<double> _position;
    maths::Vector3<double> _angle;
    maths::Vector2<std::size_t> _resolution;
    double _fov;
};

}  // namespace rtx::scene
