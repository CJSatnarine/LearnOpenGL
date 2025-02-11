#include "ElementBufferObject.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "debug.h"
#include "glad/glad.h"
#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

// Prototypes
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// Constants
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

// Vertices.
float vertices[] = {
    //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Lower left corner
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Upper left corner
    0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Upper right corner
    0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f  // Lower right corner
};

// Indices.
unsigned int indices[] = {
    0, 2, 1, // upper triangle
    0, 3, 2  // lower triangle
};

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

    // Generates VAO and binds it.
    VertexArrayObject VAO;
    VAO.Bind();

    // Generates VBO and links it to vertices.
    VertexBufferObject VBO(vertices, sizeof(vertices));
    VBO.Bind();

    // Generates EBO and links it to indices.
    ElementBufferObject EBO(indices, sizeof(indices));
    EBO.Bind();

    // Links VBO attributes to VAO.
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float),
                   (void *)(3 * sizeof(float)));
    VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float),
                   (void *)(6 * sizeof(float)));

    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();

    // Gets ID of uniform called "scale".
    unsigned int uniformID = glGetUniformLocation(shader.ID, "scale");

    // Texture stuff
    LogInfo("creating texture.");
    Texture face("../src/texture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA,
                 GL_UNSIGNED_BYTE);
    face.textureUnit(shader, "tex0", 0);

    // Render loop.
    while (!glfwWindowShouldClose(window)) {
        // Input.
        processInput(window);

        // Rendering the background.
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Rendering the triangle.
        shader.Activate();

        // Assigns a value to the uniform. (Must be always done before
        // activating.)
        glUniform1f(uniformID, 0.5f);

        face.Bind();
        VAO.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Call events and swap buffers.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Delete all the objects created.
    VAO.Delete();
    VBO.Delete();
    EBO.Delete();
    face.Delete();
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
