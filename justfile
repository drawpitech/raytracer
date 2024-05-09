outdir := env("BUILD_OUT", "build")

# Build (release)
release: (_build "Release" "NONE")

# Build (debug)
debug: (_build "Debug" "NONE")

# Build (address sanitizer)
asan: (_build "Debug" "MEMORY")

# Build (thread sanitizer)
tsan: (_build "Debug" "THREAD")

_build type sanitizer:
    cmake -S . -B {{ outdir }} -DCMAKE_BUILD_TYPE={{ type }} -DSANITIZER={{ sanitizer }}
    cmake --build {{ outdir }} -j {{ num_cpus() }}

# Format all files
format:
    fd --glob "*.{cpp,hpp}" --exec-batch clang-format -i -style=file

# Clean build output
clean:
    rm -r {{ outdir }}
