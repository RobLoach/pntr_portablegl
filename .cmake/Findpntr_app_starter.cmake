find_package(pntr REQUIRED)
find_package(pntr_app REQUIRED)

list(APPEND LIBRARIES
    pntr
    pntr_app
)

list(TRANSFORM SOURCES PREPEND ${PROJECT_SOURCE_DIR}/)

# Resources
if (EXISTS ${PROJECT_SOURCE_DIR}/resources)
    file(GLOB resources ${PROJECT_SOURCE_DIR}/resources/*)
    set(examples_resources)
    list(APPEND examples_resources ${resources})
    file(COPY ${examples_resources} DESTINATION "resources/")
    set(EMSCRIPTEN_RESOURCES "--preload-file ${PROJECT_SOURCE_DIR}/resources@/resources")
else()
    set(EMSCRIPTEN_RESOURCES "")
endif()

if (RAYLIB)
    find_package(raylib QUIET)
    set(project_name_raylib ${PROJECT_NAME}_raylib)

    add_executable(${project_name_raylib}
        ${SOURCES}
    )

    target_link_libraries(${project_name_raylib} PUBLIC
        raylib_static
        ${LIBRARIES}
    )

    # Platform Updates
    if (EMSCRIPTEN)
        set_target_properties(${project_name_raylib} PROPERTIES OUTPUT_NAME "index")
        set_target_properties(${project_name_raylib} PROPERTIES SUFFIX ".html")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY --preload-file ${PROJECT_SOURCE_DIR}/resources@/resources --shell-file ${CMAKE_CURRENT_LIST_DIR}/shell.html")

        target_compile_definitions(${project_name_raylib} PUBLIC
            PLATFORM=Web
        )
    else()
        set_property(TARGET ${project_name_raylib} PROPERTY C_STANDARD 99)
    endif()

    if (APPLE AND NOT EMSCRIPTEN)
        target_link_libraries(${project_name_raylib} PUBLIC "-framework IOKit")
        target_link_libraries(${project_name_raylib} PUBLIC "-framework Cocoa")
        target_link_libraries(${project_name_raylib} PUBLIC "-framework OpenGL")
    endif()

    target_compile_definitions(${project_name_raylib} PUBLIC
        PNTR_APP_RAYLIB
    )
endif()

if (CLI AND NOT EMSCRIPTEN)
    set(project_name_cli ${PROJECT_NAME}_cli)

    add_executable(${project_name_cli}
        ${SOURCES}
    )
    target_compile_definitions(${project_name_cli} PUBLIC
        PNTR_APP_CLI
    )
    target_link_libraries(${project_name_cli} PUBLIC
        ${LIBRARIES}
    )
    set_property(TARGET ${project_name_cli} PROPERTY C_STANDARD 99)
endif()

if (LIBRETRO AND NOT EMSCRIPTEN)
    find_package(libretrocommon REQUIRED)
    find_package(libretrodeps REQUIRED)
    set(project_name_libretro ${PROJECT_NAME}_libretro)

    add_custom_target(${project_name_libretro} ALL
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )

    add_custom_command(
        TARGET ${project_name_libretro}
        POST_BUILD
        COMMAND
            LIBRETRO_COMMON_DIR=${libretrocommon_SOURCE_DIR}
            LIBRETRO_DEPS_DIR=${libretrodeps_SOURCE_DIR}
            PNTR_DIR=${pntr_SOURCE_DIR}
            PNTR_APP_DIR=${pntr_app_SOURCE_DIR}
            TARGET_NAME=${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
            CORE_DIR=${PROJECT_SOURCE_DIR}
            SOURCES=${SOURCES}
            make
        VERBATIM
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        COMMAND_EXPAND_LISTS
    )
endif()

# Emscripten
if (WEB AND EMSCRIPTEN)
    set(project_name_web ${PROJECT_NAME}_web)

    add_executable(${project_name_web}
        ${SOURCES}
    )
    target_compile_definitions(${project_name_web} PUBLIC
        PNTR_APP_WEB
    )
    target_link_libraries(${project_name_web} PUBLIC
        ${LIBRARIES}
    )
    set_target_properties(${project_name_web} PROPERTIES SUFFIX ".html")
    set_target_properties(${project_name_web} PROPERTIES OUTPUT_NAME "index")
    set_property(TARGET ${project_name_web} PROPERTY C_STANDARD 99)
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release")
    endif()

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O3 -s WASM=1 ${EMSCRIPTEN_RESOURCES} --shell-file ${CMAKE_CURRENT_LIST_DIR}/shell.html")
endif()
