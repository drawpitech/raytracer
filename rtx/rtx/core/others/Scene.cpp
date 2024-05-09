/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Scene.cpp
*/

#include "Scene.hpp"

#include <utility>

namespace rtx::others {
void Scene::addObject(std::unique_ptr<render::IObject> object) {
    _objects.emplace_back(std::move(object));
    _renderable_vector.emplace_back(_objects.back().get());
}

void Scene::addLight(std::unique_ptr<render::DirectionalLights> light) {
    _lights.emplace_back(std::move(light));
    _renderable_lights.emplace_back(_lights.back().get());
}

void Scene::setAmbientLight(const render::AmbientLight &light) {
    _ambient_light = light;
}

const render::RenderableVector &Scene::objects() const {
    return _renderable_vector;
}

ThreadedScene Scene::threadedScene() const {
    return ThreadedScene{_renderable_vector, _renderable_lights, _config, _ambient_light};
}

ThreadedScene::ThreadedScene(
    render::RenderableVector renderable_vector,
    std::vector<const render::DirectionalLights *> renderable_lights,
    const RenderConfig &config,
    const render::AmbientLight &ambient_light
)
    : _config{&config},
      _renderable_vector{std::move(renderable_vector)},
      _renderable_lights{std::move(renderable_lights)},
      _ambient_light{&ambient_light} {}

const render::RenderableVector &ThreadedScene::objects() const {
    return _renderable_vector;
}

const std::vector<const render::DirectionalLights *> &ThreadedScene::lights() const {
    return _renderable_lights;
}

const RenderConfig &ThreadedScene::config() const {
    return *_config;
}

const render::AmbientLight &ThreadedScene::ambientLight() const {
    return *_ambient_light;
}

Scene::Scene(const RenderConfig &config) : _config{config} {}
}  // namespace rtx::others
