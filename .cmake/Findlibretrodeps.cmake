# libretro-deps
include(FetchContent)
FetchContent_Declare(
    libretrodeps
    GIT_REPOSITORY https://github.com/libretro/libretro-deps.git
    GIT_TAG c8638d7d317c397c19aa4551038bf648a467ffe6
    GIT_SHALLOW 1
)
FetchContent_MakeAvailable(libretrodeps)
#include_directories(${libretrocommon_SOURCE_DIR})
