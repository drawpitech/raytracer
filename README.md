# raytracer

A simple raytracer written in C++.
Outputs a image.ppm file.

> [!NOTE]
> This project has been made for a project of the second year at Epitech, and is
> part of the course "Object oriented programming".

- [Baptiste](https://github.com/baptiste0928)
- [Jacques](https://github.com/JacquesHumule)
- [Clément](https://github.com/drawbu)

![out](https://github.com/baptiste0928/epitech-raytracer/assets/69208565/c4a3d261-e26c-4087-aaf6-e3b442ec5857)

## Usage

At the root of the project, you can find a (scene.cfg)[./scene.cfg] file. You
can modify this file to change the scene.

```cfg
# Configuration of the camera
camera: {
  position =   { x = 0., y = 0., z = 0. }
  angle =      { x = 0., y = 0., z = 180. } # In degres
  resolution = { width = 1800, height = 1200 }
  fov =        90.
}

# Configuration of the scene
scene: {
  max_bounces = 10,     # optional. default value: 5
  samples = 100,        # optional. default value: 10
  render_mode = "fast", # optional. default value: "fast"
  # options: "fast", "path_tracing"

  ambient_light = {
    intensity = 0.1
    color = { r = 25, g = 25, b = 25 },
  }

  # Array of objects
  # options: "sphere", "plane"
  objects: (
    { type = "sphere",
      position = { x = 0., y = -1., z = 0. },
      radius = 0.5,
      material = { diffuse = { r = 255, g = 0, b = 0 } }
    },

    { type = "plane",
      normal = { x = 0., y = 0., z = 1.},
      position = { x = 0., y = 0., z = -0.5 },
      material = { diffuse = { r = 128, g = 128, b = 128 } }
    },
   )

  # Array of directional lights
  lights: (
    { direction = { x = 1., y = -1., z = -1. },
      intensity = 1.
      color = { r = 255, g = 255, b = 255 },
    },
  )
}
```

## Build

There is a lot of possibility if your want to build.

### Justfile

All the build configuration are in the justfile.
The binary will be built to `./build/raytracer`.
```sh
just release # build with optimizations
just debug   # build with debug symbols
just asan    # build with address sanitizer
just tsan    # build with thread sanitizer
```

### Nix

All the binaries are available through a Nix flake.
The binary will be built to `./result/bin/raytracer`.
```sh
nix build         # build with optimizations
nix build .#debug # build with debug symbols
nix build .#asan  # build with address sanitizer
nix build .#tsan  # build with thread sanitizer
```

### CMake

Or you can use CMake directly.
You will need several dependencies (available through the Nix flake, or you can
install them manually):
- CMake >= 3.27
- A C++ compiler that does supports C++20
- libconfig++

```sh
# This is an example for release build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DSANITIZER=None
cmake --build build -j
# The binary will be built to `./build/raytracer`.
```

## Running

The binary does not take any argument.
```sh
./raytracer
```
