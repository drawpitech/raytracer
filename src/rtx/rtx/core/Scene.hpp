/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Scene.hpp
*/

#pragma once
#include <memory>
#include <vector>

#include "Object.hpp"

namespace rtx::core {
class Scene {
   public:
    Scene() = default;
    ~Scene() = default;

    Scene(const Scene &) = delete;
    Scene(Scene &&) = default;

    Scene &operator=(const Scene &) = delete;
    Scene &operator=(Scene &&) = default;

    // basics::Camera &addCamera(std::unique_ptr<basics::Camera> camera);
    // [[nodiscard]] basics::Camera &defaultCamera() const;

    Object &addObject(std::unique_ptr<Object> object);

    [[nodiscard]] const std::vector<const Object *> &objects() const;

    // [[nodiscard]] Image render(RenderingInstance &viewport) const;

   private:
    std::vector<std::unique_ptr<Object>> _objects;

    std::vector<const Object *> _object_refs;

    // std::vector<std::unique_ptr<basics::Camera>> _cameras;
    // basics::Camera *_default_camera{nullptr};
};
}  // namespace rtx::core
