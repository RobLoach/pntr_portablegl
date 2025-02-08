# libretro-deps
include(FetchContent)
FetchContent_Declare(
    libretrodeps
    GIT_REPOSITORY https://github.com/libretro/libretro-deps.git
    GIT_TAG c273a49
)
FetchContent_MakeAvailable(libretrodeps)
#include_directories(${libretrocommon_SOURCE_DIR})
