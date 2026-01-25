# libretro-common
include(FetchContent)
FetchContent_Declare(
    libretrocommon
    GIT_REPOSITORY https://github.com/libretro/libretro-common.git
    GIT_TAG  (#224)
76a3d54
)
FetchContent_MakeAvailable(libretrocommon)
#include_directories(${libretrocommon_SOURCE_DIR})
