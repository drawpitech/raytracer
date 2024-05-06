include(FindPkgConfig)
pkg_check_modules(LIBCONFIG REQUIRED libconfig++)
include_directories(${LIBCONFIG_INCLUDE_DIRS})

add_library(rtx_core
        Core.cpp
        Scene.cpp
        Config.cpp
        Color.cpp
        Hitpoint.cpp
        Image.cpp
        RenderingInstance.cpp
        RenderingInstance.hpp
)

target_link_libraries(rtx_core PRIVATE rtx_maths ${LIBCONFIG_LIBRARIES})
target_include_directories(rtx_core PUBLIC ${RTX_INCLUDE_DIRS})
target_compile_features(rtx_core PUBLIC cxx_std_20)
