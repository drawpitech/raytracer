/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RenderCluster.cpp
*/

#include "RenderCluster.hpp"

#include <rtx/core/render/RenderPixel.hpp>

namespace rtx::others {
void RenderCluster::render() const {
    for (size_t j = 0; j < _rect.size().y(); j++) {
        for (size_t i = 0; i < _rect.size().x(); i++) {
            maths::Point2 point{i + _rect.point().x(), j + _rect.point().y()};
            _image->setPixel(point, render::RenderPixel{*_scene, *_viewport}.render(point));
        }
    }
}
}  // namespace rtx::others
