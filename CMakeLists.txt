cmake_minimum_required(VERSION 3.20)

project(learnopengl-study LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)

add_executable(learnopengl-study
    src/main.cpp
)

target_link_libraries(learnopengl-study
    PRIVATE
    glfw
)