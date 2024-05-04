add_library(rtx_maths
        Matrix.hpp
        Vector.hpp
        types.hpp
        maths_concepts.hpp
        m.cpp
)

target_compile_features(rtx_maths PUBLIC cxx_std_20)
