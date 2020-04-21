cmake_minimum_required(VERSION 3.0)

# Set dependencies
find_library(qcore ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# Create qcore shared library
add_library(vc-plugin SHARED
   src/VCPlayer.cpp
   src/PlayerRegistration.cpp
)

target_compile_options(vc-plugin PRIVATE -Werror -Wall -Wextra)
target_include_directories(vc-plugin PUBLIC include)
target_link_libraries(vc-plugin qcore)
