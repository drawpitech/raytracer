/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Camera.cpp
*/

#include "Camera.hpp"

#include <rtx/maths/Matrix.hpp>
#include <rtx/maths/Point.hpp>
#include <rtx/maths/Rectangle.hpp>

#include <cmath>

#include "Viewport.hpp"

namespace rtx::others {

Camera::Camera(
    maths::Point3<double> position,
    maths::Vector3<double> angle,
    maths::Vector2<std::size_t> resolution,
    double fov
)
    : _position{position}, _angle{angle}, _resolution{resolution}, _fov{fov} {}

Viewport Camera::viewport() {
    const double tan_hfov = std::tan(_fov / 2);
    const double ratio =
        static_cast<double>(_resolution.x()) / static_cast<double>(_resolution.y());
    const double hvfov = tan_hfov / ratio;

    const auto transform = translation_matrix(maths::Point3<double>{}.vectorTo(_position))
                               .dot(maths::rotation_xyz_matrix(_angle.x(), _angle.y(), _angle.z()));

    maths::Rectangle3 rect{
        matrix_to_point(transform.dot(maths::Point3{tan_hfov, 1., hvfov}.toMatrix())),
        matrix_to_point(transform.dot(maths::Point3{-tan_hfov, 1., hvfov}.toMatrix())),
        matrix_to_point(transform.dot(maths::Point3{tan_hfov, 1., -hvfov}.toMatrix()))
    };
    return {rect, _resolution, _position};
}

RenderInstance Camera::renderingInstance(const ThreadedScene &scene) {
    return {scene, viewport(), _resolution};
}
}  // namespace rtx::others
