set(RTX_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(rtx/core)
add_subdirectory(rtx/maths)
add_subdirectory(rtx/render)

add_library(rtx INTERFACE)

target_link_libraries(rtx INTERFACE rtx_core)
target_link_libraries(rtx INTERFACE rtx_maths)
target_link_libraries(rtx INTERFACE rtx_render)


message(STATUS "rtx include dirs: ${RTX_INCLUDE_DIRS}")

target_include_directories(rtx INTERFACE $<BUILD_INTERFACE:${RTX_INCLUDE_DIRS}>)
