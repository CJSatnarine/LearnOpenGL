cmake_minimum_required(VERSION 3.5.0)
project(first_opengl_project VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(
    first_opengl_project
    src/main.cpp
    src/glad/glad.c
    src/glad/glad.h
    src/Shader.h
    src/Shader.cpp
    src/fragmentShader.glsl
    src/vertexShader.glsl
)

target_link_libraries(first_opengl_project glfw OpenGL::GL)
