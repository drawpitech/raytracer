add_executable(raytracer main.cpp)

target_compile_features(raytracer PRIVATE cxx_std_20)

target_link_libraries(raytracer PRIVATE rtx)
