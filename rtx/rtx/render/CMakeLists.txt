file(GLOB_RECURSE RTX_RENDER_HEADERS CONFIGURE_DEPENDS "*.hpp")
file(GLOB_RECURSE RTX_RENDER_SOURCES CONFIGURE_DEPENDS "*.cpp")
add_library(rtx_render ${RTX_RENDER_HEADERS} ${RTX_RENDER_SOURCES})

target_link_libraries(rtx_render PRIVATE rtx_maths rtx_core)
