# libretro-common
include(FetchContent)
FetchContent_Declare(
    libretrocommon
    GIT_REPOSITORY https://github.com/libretro/libretro-common.git
    GIT_TAG ad9124f
)
FetchContent_MakeAvailable(libretrocommon)
#include_directories(${libretrocommon_SOURCE_DIR})
