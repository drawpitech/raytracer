/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Hitpoint.cpp
*/

#include "Hitpoint.hpp"

namespace rtx::core {
Hitpoint::Hitpoint(
    const maths::Ray3<double>& ray, const double distance,
    const maths::Point3<double>& point, const maths::Vector3<double>& normal)
    : _ray{ray}, _distance{distance}, _point{point}, _normal{normal} {}
const maths::Ray3<double>& Hitpoint::ray() const {
    return _ray;
}
const double& Hitpoint::distance() const {
    return _distance;
}
const maths::Point3<double>& Hitpoint::point() const {
    return _point;
}
const maths::Vector3<double>& Hitpoint::normal() const {
    return _normal;
}

}  // namespace rtx::core
