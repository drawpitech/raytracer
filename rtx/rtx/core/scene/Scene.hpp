/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Scene.hpp
*/

#pragma once
#include <rtx/core/render/AmbientLight.hpp>
#include <rtx/core/render/DirectionalLights.hpp>
#include <rtx/core/render/IObject.hpp>
#include <rtx/core/render/RenderableVector.hpp>

#include <memory>
#include <variant>
#include <vector>

namespace rtx::scene {

namespace settings {
enum class Antialiasing : unsigned char {
    NONE,
    MSAA_X4,
};

struct FastRenderConfig {
    Antialiasing antialiasing{Antialiasing::MSAA_X4};
};

struct PathTracerRenderConfig {
    unsigned samples;
    unsigned max_bounces;
    Antialiasing antialiasing;
};
};  // namespace settings

using RenderConfig = std::variant<settings::FastRenderConfig, settings::PathTracerRenderConfig>;

class SceneRef {
   public:
    SceneRef(
        RenderConfig config,
        render::RenderableVector objects,
        std::vector<const render::DirectionalLight *> lights,
        render::AmbientLight ambient_light
    )
        : _config{config},
          _objects{std::move(objects)},
          _lights{std::move(lights)},
          _ambient_light{ambient_light} {}

    [[nodiscard]] const RenderConfig &config() const {
        return _config;
    }

    [[nodiscard]] const render::RenderableVector &objects() const {
        return _objects;
    }

    [[nodiscard]] const std::vector<const render::DirectionalLight *> &lights() const {
        return _lights;
    }

    [[nodiscard]] const render::AmbientLight &ambientLight() const {
        return _ambient_light;
    }

   private:
    RenderConfig _config;
    render::RenderableVector _objects;
    std::vector<const render::DirectionalLight *> _lights;
    render::AmbientLight _ambient_light;
};

class Scene {
   public:
    explicit Scene(const RenderConfig &config) : _config{config} {}

    ~Scene() = default;

    Scene(const Scene &) = delete;
    Scene(Scene &&) = default;

    Scene &operator=(const Scene &) = delete;
    Scene &operator=(Scene &&) = default;

    void addObject(std::unique_ptr<render::IObject> object);
    void addLight(std::unique_ptr<render::DirectionalLight> light);
    void setAmbientLight(render::AmbientLight light);

    [[nodiscard]] SceneRef asRef() const;

   private:
    RenderConfig _config;
    std::vector<std::unique_ptr<render::IObject>> _objects;
    std::vector<std::unique_ptr<render::DirectionalLight>> _lights;
    render::AmbientLight _ambient_light{{0, 0, 0}, 0};
};

}  // namespace rtx::scene
