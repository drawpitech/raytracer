include(FindPkgConfig)

pkg_check_modules(LIBCONFIG REQUIRED libconfig++)
include_directories(${LIBCONFIG_INCLUDE_DIRS})

pkg_check_modules(SFML REQUIRED sfml-system sfml-window sfml-graphics)
include_directories(${SFML_INCLUDE_DIRS})

file(GLOB_RECURSE RTX_CORE_HEADERS CONFIGURE_DEPENDS "*.hpp")
file(GLOB_RECURSE RTX_CORE_SOURCES CONFIGURE_DEPENDS "*.cpp")
add_library(rtx_core ${RTX_CORE_HEADERS} ${RTX_CORE_SOURCES}
        shapes/Cone.cpp
        shapes/Cone.hpp)

target_link_libraries(rtx_core PRIVATE rtx_maths ${LIBCONFIG_LIBRARIES} ${SFML_LIBRARIES})
target_include_directories(rtx_core PUBLIC ${RTX_INCLUDE_DIRS})
target_compile_features(rtx_core PUBLIC cxx_std_20)
