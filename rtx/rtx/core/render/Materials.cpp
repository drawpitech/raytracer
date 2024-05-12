/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Materials.cpp
*/

#include "Materials.hpp"

#include <algorithm>

namespace rtx::render {

Materials::Materials(const Color &diffuse) : _diffuse{diffuse} {}

Color Materials::render(const Hitpoint &hitpoint, const scene::SceneRef &scene) const {
    if (std::holds_alternative<scene::settings::FastRenderConfig>(scene.config())) {
        return fastRender(hitpoint, scene);
    }
    return {0, 0, 0};
}

Color Materials::fastRender(const Hitpoint &hitpoint, const scene::SceneRef &scene) const {
    auto c_light = Color{0, 0, 0};
    double weight = 0;

    if (std::ranges::all_of(
            scene.lights(),
            [hitpoint](const auto &light) {
                return hitpoint.normal().dot(-light->direction()) <= 0;
            }
        ) ||
        std::ranges::all_of(scene.lights(), [hitpoint, scene](const auto &light) {
            return scene.objects()
                .hit({hitpoint.point(), -light->direction()}, hitpoint.object())
                .has_value();
        })) {
        return _diffuse * scene.ambientLight().color * scene.ambientLight().intensity;
    }
    int i = 0;
    for (const auto &light : scene.lights()) {
        auto angle = hitpoint.normal().dot(-light->direction());
        if (angle > 0 &&
            !scene.objects().hit({hitpoint.point(), -light->direction()}, hitpoint.object())) {
            i++;
            c_light = {
                std::max(c_light.r(), angle * light->color().r() * light->intensity()),
                std::max(c_light.g(), angle * light->color().g() * light->intensity()),
                std::max(c_light.b(), angle * light->color().b() * light->intensity())
            };
            weight += angle;
        }
    }

    return _diffuse * (c_light + (1 - weight / i) * scene.ambientLight().color *
                                     scene.ambientLight().intensity);
}

}  // namespace rtx::render
