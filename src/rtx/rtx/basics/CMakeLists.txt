add_library(rtx_basics
        Camera.cpp
        Viewport.cpp
        Camera.cpp
        Sphere.cpp
)

target_link_libraries(rtx_basics PRIVATE rtx_maths rtx_core)


#target_include_directories(rtx_basics INTERFACE
#        $<BUILD_INTERFACE:${RTX_INCLUDE_DIRS}>)
