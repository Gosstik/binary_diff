# NODE: this module depends on third-party CodeCoverage.cmake

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#add_compile_definitions()

add_compile_options(-Wall -Wextra -Wpedantic -g -fno-omit-frame-pointer)

if(DEVELOPMENT_MODE)
    project_log("Turn warnings into errors.")
    add_compile_options(-Werror)
endif()


#if (TOOLBOX_COVERAGE)
#    project_log("Turn off optimisation (flag -O0) for coverage.")
#    add_compile_options(-O0)
#    append_coverage_compiler_flags()
#endif()
