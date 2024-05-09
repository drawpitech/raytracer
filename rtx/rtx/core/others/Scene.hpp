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
#include <vector>

namespace rtx::others {
struct RenderConfig {
    enum class RenderMode : unsigned char {
        FAST,
        PATH_TRACER,
    };

    unsigned samples;
    unsigned max_bounces;
    RenderMode mode;
};

class ThreadedScene {
   public:
    ThreadedScene(
        render::RenderableVector renderable_vector,
        std::vector<const render::DirectionalLights *> renderable_lights,
        const RenderConfig &config,
        const render::AmbientLight &ambient_light
    );

    [[nodiscard]] const render::RenderableVector &objects() const;
    [[nodiscard]] const std::vector<const render::DirectionalLights *> &lights() const;

    [[nodiscard]] const RenderConfig &config() const;

    [[nodiscard]] const render::AmbientLight &ambientLight() const;

   private:
    const RenderConfig *_config;
    render::RenderableVector _renderable_vector;
    std::vector<const render::DirectionalLights *> _renderable_lights;
    const render::AmbientLight *_ambient_light;
};

class Scene {
   public:
    explicit Scene(const RenderConfig &config);
    ~Scene() = default;

    Scene(const Scene &) = delete;
    Scene(Scene &&) = default;

    Scene &operator=(const Scene &) = delete;
    Scene &operator=(Scene &&) = default;

    void addObject(std::unique_ptr<render::IObject> object);
    void addLight(std::unique_ptr<render::DirectionalLights> light);

    void setAmbientLight(const render::AmbientLight &light);

    [[nodiscard]] const render::RenderableVector &objects() const;
    [[nodiscard]] const std::vector<const render::DirectionalLights *> &lights() const;

    [[nodiscard]] ThreadedScene threadedScene() const;

   private:
    RenderConfig _config;
    std::vector<std::unique_ptr<render::IObject>> _objects;
    std::vector<std::unique_ptr<render::DirectionalLights>> _lights;

    render::RenderableVector _renderable_vector;
    std::vector<const render::DirectionalLights *> _renderable_lights;
    render::AmbientLight _ambient_light{{0, 0, 0}, 0};
};

}  // namespace rtx::others
