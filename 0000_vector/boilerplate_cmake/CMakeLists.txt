cmake_minimum_required(VERSION 3.14.0)

set(ARCHEUS_STD_VERSION 0.0.0)
project(archeus_std LANGUAGES C VERSION ${ARCHEUS_STD_VERSION} DESCRIPTION "libarcheus_std standard archeus c library")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    message("[Archeus C STD] Build Type not set, defaulting to Debug")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Default to Debug" FORCE)
endif()

add_compile_options(
  "-Wall" "-Wextra" "-Werror" "-Wpedantic" "-fexceptions" ""
  "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb;-DARC_DEBUG;-DARC_DEBUG_LOG_STREAM_OVERRIDE;>"
  "$<$<CONFIG:RELEASE>:-02;-g;>"
)

# ~ ARCHEUS_SOURCES ~ #
set(ARCHEUS_STD_SOURCES
    src/std/errno.c
    src/std/vector.c
)

add_executable(tests
    tests/test.c

    tests/std/vector.c

    ${ARCHEUS_STD_SOURCES}
)

target_include_directories(tests
    PRIVATE include
)
