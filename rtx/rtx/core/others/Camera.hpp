/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Camera.hpp
*/

#pragma once

#include <rtx/maths/Rectangle.hpp>

#include "RenderInstance.hpp"
#include "Viewport.hpp"

namespace rtx::others {

class Camera {
   public:
    Camera(
        maths::Point3<double> position,
        maths::Vector3<double> angle,
        maths::Vector2<std::size_t> resolution,
        double fov
    );

    maths::Point3<double> &position();
    [[nodiscard]] const maths::Point3<double> &position() const;

    maths::Vector3<double> &angle();
    [[nodiscard]] const maths::Vector3<double> &angle() const;

    maths::Point2<double> &resolution();
    [[nodiscard]] const maths::Point2<double> &resolution() const;

    double &fov();
    [[nodiscard]] const double &fov() const;

    Viewport viewport();
    Viewport viewport(maths::Rectangle2<std::size_t> rect);

    RenderInstance renderingInstance(const ThreadedScene &scene);
    RenderInstance renderingInstance(maths::Rectangle2<std::size_t> rect);

   private:
    maths::Point3<double> _position;
    maths::Vector3<double> _angle;
    maths::Vector2<std::size_t> _resolution;
    double _fov;
};

}  // namespace rtx::others
