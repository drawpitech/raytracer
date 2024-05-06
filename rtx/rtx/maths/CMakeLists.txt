file(GLOB_RECURSE RTX_MATHS_HEADERS CONFIGURE_DEPENDS "*.hpp")
add_library(rtx_maths INTERFACE ${RTX_MATHS_HEADERS})

target_compile_features(rtx_maths INTERFACE cxx_std_20)

target_include_directories(rtx_maths INTERFACE ${RTX_INCLUDE_DIRS})
