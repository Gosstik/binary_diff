cmake_minimum_required(VERSION 3.26)
project(1C_project)

# --------------------------------------------------------------------

# Options

option(DEVELOPMENT_MODE "Enable development mode." ON)

# --------------------------------------------------------------------

# cmake setup

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(Color)
include(Logging)
# include(BuildTest)
# include(third-party/CodeCoverage)
# include(Coverage)

#add_subdirectory(third_party)

# This must be included after library so that third party code is not affected.
include(CompileOptions)

# Uncomment next lines to save binary files in special dirs.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# --------------------------------------------------------------------

# Build project.

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
