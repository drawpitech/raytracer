add_executable(raytracer main.cpp)

set_target_properties(raytracer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

target_compile_features(raytracer PRIVATE cxx_std_20)

target_link_libraries(raytracer PRIVATE rtx)
