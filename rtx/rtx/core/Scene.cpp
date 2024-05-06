/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Scene.cpp
*/

#include "Scene.hpp"

namespace rtx::core {
// rtx::basics::Camera& rtx::core::Scene::addCamera(
//     std::unique_ptr<basics::Camera> camera) {
//     _cameras.emplace_back(std::move(camera));
//     if (_default_camera == nullptr) {
//         _default_camera = _cameras.back().get();
//     }
//     return *_cameras.back();
// }
// rtx::basics::Camera& rtx::core::Scene::defaultCamera() const {
//     if (_default_camera == nullptr) {
//         throw std::runtime_error("No default camera");
//     }
//     return *_default_camera;
// }
Object& Scene::addObject(std::unique_ptr<Object> object) {
    _objects.emplace_back(std::move(object));
    _object_refs.emplace_back(_objects.back().get());
    return *_objects.back();
}
const std::vector<const Object*>& Scene::objects() const {
    return _object_refs;
}
// rtx::core::Image rtx::core::Scene::render(
//     RenderingInstance& rendering_instance) const {
//     for (size_t i = 0; i < rendering_instance._resolution.x(); i++) {
//         for (size_t j = 0; j < viewport.resolution().y(); j++) {
//             auto ray =
//                 viewport.ray({static_cast<double>(i),
//                 static_cast<double>(j)});
//             std::optional<Hitpoint> hitpoint;
//             for (const auto& object : _objects) {
//                 const auto tmp = object->hit(ray);
//                 if (!tmp) {
//                     continue;
//                 }
//                 if (!hitpoint || tmp->distance() < hitpoint->distance()) {
//                     hitpoint = tmp;
//                 }
//             }
//             if (hitpoint) {
//                 image.setPixel({i, j},
//                 Color::fromNormal(hitpoint->normal()));
//             } else {
//                 image.setPixel({i, j},
//                 sky(ray.direction().normalized().z()));
//             }
//         }
//     }
//
//     return image;
// }
}  // namespace rtx::core
