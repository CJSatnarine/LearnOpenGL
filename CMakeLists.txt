cmake_minimum_required(VERSION 3.5.0)
project(first_opengl_project VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(
    first_opengl_project
    src/main.cpp
    src/glad/glad.c
    src/glad/glad.h
    src/classes/Shader.h
    src/classes/Shader.cpp
    src/classes/debug.cpp
    src/classes/debug.h
    src/shaders/fragmentShader.glsl
    src/shaders/vertexShader.glsl
    src/classes/ElementBufferObject.h 
    src/classes/ElementBufferObject.cpp
    src/classes/VertexArrayObject.h 
    src/classes/VertexArrayObject.cpp
    src/classes/VertexBufferObject.h 
    src/classes/VertexBufferObject.cpp
    src/stb/stb_image.h 
    src/stb/stb.cpp
    src/classes/Texture.h 
    src/classes/Texture.cpp
    src/resources/texture.png
)

target_link_libraries(first_opengl_project glfw OpenGL::GL)
