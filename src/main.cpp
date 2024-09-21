// OpenGL stuff.
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <cstddef>
#include <iostream>

// Prototypes.
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Creation of window.
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    // If window isn't created.
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Make the context of the window the main context on the current thread. 
    glfwMakeContextCurrent(window);

    // Initialising GLAD. 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialise GLAD" << std::endl;
        return -1;
    }

    /*
    * Viewport
    *
    * Tells OpenGL the size of the rendering window so OpenGL knows
    * how we want to display the data and coordinates with respect to
    * the window. 
    * 
    * The first two paramaters set the location of the lower left corner
    * of the window. 
    * The last two parameters set the width and height of the window in pixels.  
    */
   glViewport(0, 0, 800, 600);

    // Managing window resizing. 
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Window closing with the ESC key. 
    while (!glfwWindowShouldClose(window)) {
        // Input. 
        processInput(window);

        // Rendering commands. 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Check and call events and swap the buffers. 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Looping the window until close.
    while(!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up GLFW's resources that were allocated. 
    glfwTerminate();
    return 0;
}

// Resizing function to deal with resizing the window. 
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Window closing with ESC key. 
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
