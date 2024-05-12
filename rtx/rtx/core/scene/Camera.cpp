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

namespace rtx::scene {

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

maths::Point3<double> &Camera::position() {
    return _position;
}

const maths::Point3<double> &Camera::position() const {
    return _position;
}

maths::Vector3<double> &Camera::angle() {
    return _angle;
}

const maths::Vector3<double> &Camera::angle() const {
    return _angle;
}

maths::Vector2<size_t> &Camera::resolution() {
    return _resolution;
}

const maths::Vector2<size_t> &Camera::resolution() const {
    return _resolution;
}

double &Camera::fov() {
    return _fov;
}

const double &Camera::fov() const {
    return _fov;
}

}  // namespace rtx::scene
