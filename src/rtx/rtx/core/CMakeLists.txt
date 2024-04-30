include(FindPkgConfig)
pkg_check_modules(LIBCONFIG REQUIRED libconfig++)
include_directories(${LIBCONFIG_INCLUDE_DIRS})

add_library(rtx_core Core.cpp Scene.cpp Config.cpp)

target_link_libraries(rtx_core PUBLIC ${LIBCONFIG_LIBRARIES})
