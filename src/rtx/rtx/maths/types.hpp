/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** types.cpp
*/

#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"

namespace rtx::maths {
template <typename T>
using Point2 = Vector2<T>;

template <typename T>
using Point3 = Vector3<T>;
}  // namespace rtx::maths
