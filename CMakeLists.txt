cmake_minimum_required(VERSION 3.26)
project(1C_project)

# --------------------------------------------------------------------

# cmake setup

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(Color)
include(Logging)
# include(Helpers)
# include(BuildTest)
# include(third-party/CodeCoverage)
# include(Coverage)

#add_subdirectory(third_party)

# This must be included after library so that third party code is not affected.
#include(CompileOptions)

# ----------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#add_compile_definitions()

add_compile_options(-Wall -Wextra -Wpedantic -g -fno-omit-frame-pointer)
# --------------------------------------


# Uncomment next lines to save binary files in special dirs.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# --------------------------------------------------------------------

# --------------------------------------------------------------------

# Build app.

include_directories("src")
add_subdirectory(src)

# --------------------------------------------------------------------

## Enable playground and tests.
#
#if(TOOLBOX_DEVELOPMENT)
#    add_subdirectory(playground)
#endif()
#
#if(TOOLBOX_TEST OR TOOLBOX_DEVELOPMENT OR TOOLBOX_COVERAGE)
#    add_subdirectory(tests)
#endif()

# --------------------------------------------------------------------
