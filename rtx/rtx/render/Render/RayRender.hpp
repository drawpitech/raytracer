/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RayRender.hpp
*/

#pragma once

#include <rtx/core/Types/Color.hpp>
#include <rtx/core/Scene.hpp>
#include <rtx/maths/Ray.hpp>

namespace rtx::render {

class RayRender {
   public:
    RayRender(const maths::Ray3<double> &ray, const core::Scene &scene)
        : _ray(ray), _scene(&scene) {}

    [[nodiscard]] core::Color render() const;

   private:
    maths::Ray3<double> _ray;
    const core::Scene *_scene;
};

}  // namespace rtx::render
