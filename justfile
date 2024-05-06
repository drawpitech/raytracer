outdir := env_var_or_default("BUILD_OUT", "build")

# Build (debug)
debug:
    cmake -S . -B {{outdir}} -DCMAKE_BUILD_TYPE=Debug -DSANITIZER=NONE
    cmake --build {{outdir}} -j

# Build (release)
release:
    cmake -S . -B {{outdir}} -DCMAKE_BUILD_TYPE=Release -DSANITIZER=NONE
    cmake --build {{outdir}} -j

# Build (address sanitizer)
asan:
    cmake -S . -B {{outdir}} -DCMAKE_BUILD_TYPE=Debug -DSANITIZER=MEMORY
    cmake --build {{outdir}} -j

# Build (thread sanitizer)
tsan:
    cmake -S . -B {{outdir}} -DCMAKE_BUILD_TYPE=Debug -DSANITIZER=THREAD
    cmake --build {{outdir}} -j

# Clean build output
clean:
    rm -r {{outdir}}
