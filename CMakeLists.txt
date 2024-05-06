cmake_minimum_required(VERSION 3.27)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SANITIZER "Enable sanitizers" "NONE")

option(NATIVE_CPU "Optimize for native CPU" ON)

if (SANITIZER STREQUAL "MEMORY")
    add_link_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
elseif (SANITIZER STREQUAL "THREAD")
    add_link_options(-fsanitize=thread -fno-omit-frame-pointer)
    add_compile_options(-fsanitize=thread -fno-omit-frame-pointer)
endif ()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options()
else ()
    add_compile_options(-ffast-math)
endif ()

if (NATIVE_CPU)
    add_compile_options(-march=native)
endif ()


project(Raytracer
        LANGUAGES CXX)

add_subdirectory(rtx)
add_subdirectory(app)
