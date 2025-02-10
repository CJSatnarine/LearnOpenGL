#include "Shader.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "debug.h"
#include "stb_image.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

// Prototypes
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// Constants
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

int main(void) {
    // Initialisation and configuration.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window.
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                          "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialise GLAD" << std::endl;
        return -1;
    }

    // Create shader.
    LogInfo("Creating Shaders");
    Shader shader("../src/vertexShader.glsl", "../src/fragmentShader.glsl");

    // Vertex setup.
    LogInfo("Setting up vertex");
    float vertices[] = {
        // positions         // colors
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top
    };
    // Generates VAO and binds it.
    VertexArrayObject VAO;
    VAO.Bind();

    // Generates VBO and links it to vertices.
    VertexBufferObject VBO(vertices, sizeof(vertices));
    VBO.Bind();

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // Colour attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    VAO.Unbind();
    VBO.Unbind();

    // Render loop.
    while (!glfwWindowShouldClose(window)) {
        // Input.
        processInput(window);

        // Rendering the background.
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Rendering the triangle.
        shader.Activate();

        VAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Call events and swap buffers.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Delete all the objects created.
    VAO.Delete();
    VBO.Delete();
    shader.Delete();
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
