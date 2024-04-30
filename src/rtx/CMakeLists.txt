add_subdirectory(rtx/core)
add_subdirectory(rtx/utils)
add_subdirectory(rtx/maths)

add_library(rtx INTERFACE
        rtx/maths/maths_concepts.hpp)

target_link_libraries(rtx INTERFACE rtx_core)
target_link_libraries(rtx INTERFACE rtx_utils)
#target_link_libraries(rtx INTERFACE rtx_maths)

target_include_directories(rtx INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>)
