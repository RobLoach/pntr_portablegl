# pntr_app_starter

A boilerplate starter project for applications using [pntr](https://github.com/RobLoach/pntr) and [pntr_app](https://github.com/RobLoach/pntr_app).

## Getting Started

1. Open up [CMakeLists.txt](CMakeLists.txt) and rename the project name from "pntr_app_starter" to your own application name.

    ``` cmake
    project(MyGame
        DESCRIPTION "My Game"
        VERSION 0.0.1
        LANGUAGES C
    )
    ```

2. Edit [main.c](src/main.c) as much as you'd like

## Build

The build process uses [CMake](https://cmake.org/).

A package.json is included (even though it's not a node project) to quickly document all the things you can do with `npm run`.

### Native

```
cmake -B build -DSDL=true -DRAYLIB=true -DLIBRETRO=true -DCLI=true -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Web

Use the [Emscripten SDK](https://emscripten.org/docs/tools_reference/emsdk.html) to build for the web with raylib.

```
emcmake cmake -B build -DPLATFORM=Web -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS="-s USE_GLFW=3" -DCMAKE_EXECUTABLE_SUFFIX=".html"
emmake make -C build
emrun build/index.html
```

### libretro

While the cmake definition for libretro is there, you may want to use the `make` directly.

```
LIBRETRO_COMMON_DIR=path/to/libretro-common \
LIBRETRO_DEPS_DIR=path/to/libretro-deps \
PNTR_DIR=path/to/pntr \
PNTR_APP_DIR=path/to/pntr_app \
TARGET_NAME=myproject \
CORE_DIR=. \
SOURCES=main.c \
make -C .cmake
```

## License

Unless stated otherwise, all works are:

- Copyright (c) 2023 [Rob Loach](https://robloach.net)

... and licensed under:

- [zlib License](LICENSE)
