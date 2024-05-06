add_library(rtx_render
        RayRender.cpp
)

target_link_libraries(rtx_render PRIVATE rtx_maths)
