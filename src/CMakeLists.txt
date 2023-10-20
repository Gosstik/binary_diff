set(APP_NAME "binary_diff")

add_executable("${APP_NAME}" main.cpp)

# --------------------------------------------------------------------

#add_subdirectory("SubdirName")

# --------------------------------------------------------------------

set(SOURCE
        PathManager.hpp)

#target_sources("${APP_NAME}" PRIVATE
#        "${SOURCE}")

#target_link_libraries("${APP_NAME}" PRIVATE -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system)
