cmake_minimum_required(VERSION 3.20)

project(learnopengl-study LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)

add_executable(learnopengl-study
    src/main.cpp
    external/glad/src/gl.c
)

target_include_directories(learnopengl-study
    PRIVATE
    external/glad/include
)

target_link_libraries(learnopengl-study
    PRIVATE
    glfw
)