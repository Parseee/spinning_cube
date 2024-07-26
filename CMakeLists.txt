cmake_minimum_required(VERSION 3.5.0)
project(dicer VERSION 0.1.0 LANGUAGES C)

find_package(SDL2 REQUIRED)
include_directories(dicer ${SDL2_INCLUDE_DIRS})

add_executable(dicer main.c tools.c)
target_link_libraries(dicer PRIVATE ${SDL2_LIBRARIES} SDL2_ttf)