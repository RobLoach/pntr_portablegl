cmake_minimum_required(VERSION 3.11)
project(pntr_portablegl
    DESCRIPTION "pntr_portablegl"
    HOMEPAGE_URL "https://github.com/robloach/pntr_portablegl"
    VERSION 0.0.1
    LANGUAGES C
)

# Targets
option(SDL "Build SDL" TRUE)
option(RAYLIB "Build raylib" TRUE)
option(LIBRETRO "Build libretro" FALSE)
option(CLI "Build CLI" FALSE)
option(WEB "Build Web" FALSE)

# Sources
set(SOURCES
    examples/ex2.c
)

# Libraries
#list(APPEND LIBRARIES mycustomlibrary)
list(APPEND LIBRARIES m)

# Have pntr_app_starter build the project
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/.cmake")
find_package(pntr_app_starter)
