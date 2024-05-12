/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Scene.cpp
*/

#include "Scene.hpp"

#include <rtx/core/render/RenderableVector.hpp>

#include <utility>

namespace rtx::scene {

void Scene::addObject(std::unique_ptr<shapes::AObject> object) {
    _objects.emplace_back(std::move(object));
}

void Scene::addLight(std::unique_ptr<render::DirectionalLight> light) {
    _lights.emplace_back(std::move(light));
}

void Scene::setAmbientLight(render::AmbientLight light) {
    _ambient_light = light;
}

SceneRef Scene::asRef() const {
    render::RenderableVector objects;
    std::vector<const render::DirectionalLight *> lights;

    objects.reserve(_objects.size());
    for (const auto &object : _objects) {
        objects.emplace_back(object.get());
    }

    lights.reserve(_lights.size());
    for (const auto &light : _lights) {
        lights.emplace_back(light.get());
    }

    return SceneRef{_config, objects, lights, _ambient_light};
}

}  // namespace rtx::scene
