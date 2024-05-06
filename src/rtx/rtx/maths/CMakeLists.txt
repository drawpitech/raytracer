add_library(rtx_maths INTERFACE
        Matrix.hpp
        Vector.hpp
        maths_concepts.hpp
        Point.hpp
        Rectangle.hpp
        Ray.hpp
)

target_compile_features(rtx_maths INTERFACE cxx_std_20)

target_include_directories(rtx_maths INTERFACE ${RTX_INCLUDE_DIRS})
