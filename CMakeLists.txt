cmake_minimum_required(VERSION 3.27)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Raytracer
    LANGUAGES CXX)

add_executable(raytracer app/main.cpp)
target_compile_features(raytracer PRIVATE cxx_std_20)
