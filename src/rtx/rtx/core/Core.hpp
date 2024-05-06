/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Core.hpp
*/

#pragma once

#include <string>

#include "Scene.hpp"
// #include "Config.hpp"

namespace rtx::core {
class Core {
   public:
    Core();

    void render();

    void setScene(Scene &&scene);

   private:
    Scene _scene;
};
};  // namespace rtx::core

namespace rtx {
using Core = core::Core;
}  // namespace rtx
