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

        // Making the rectangle. 
        float vertices[] = {
             0.5f,  0.5f, 0.5f, // Top Right. 
             0.5f, -0.5f, 0.0f, // Bottom Right. 
            -0.5f, -0.5f, 0.0f, // Bottom Left. 
            -0.5f,  0.5f, 0.0f  // Top Left. 
        };

        unsigned int indices[] = {
            0, 1, 3,    //First triangle.  
            1, 2, 3     // Second triangle. 
        };

        // Vertex Buffer Object (VBO), Element Buffer Object (EBO). 
        unsigned int VBO, EBO;
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Vertex shader. 
        // Vertex Shader source code in the form of a C string. 
        const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main() {\n"
        "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0)\n;"
        "}\0";
        // Create a shader object and reference it by an ID so that it can be dynamically compiled at its run time.
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        // Attach the shader code to the shader object and compile the shader. 
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        // Fragment shader. 
        // Fragment shader source code in the form of a C string (makes the colour orange).
        const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
        "}\0";
        // Compiling the fragment shader, process similar to compiling the vertex shader.
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        // Creating a shader programme object to link the shaders together. 
        unsigned int shaderProgramme;
        shaderProgramme = glCreateProgram();
        // Attaching and Linking the shaders together. 
        glAttachShader(shaderProgramme, vertexShader);
        glAttachShader(shaderProgramme, fragmentShader);
        glLinkProgram(shaderProgramme);

        // Activate the programme.
        glUseProgram(shaderProgramme);
        // Delete the shader objects since they're no longer needed once linked to the programme object.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        //Telling OpenGL how to interpret the vertex data. 
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        //Enable the vertex attribute:
        // 0. Copy our vertices array in a buffer for OpenGL to use.
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // 1. Then set the vertex attributes pointers.
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // 2. Use our shader programme when we want to render an object. 
        glUseProgram(shaderProgramme);
        // 3. Now draw the object. 
       // Some code goes here, I guess. 

        // Generate VAO. 
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);

        // Initialisation code (done once unless your object frequently changes)
        // 1. Bind Vertex Array Object.
        glBindVertexArray(VAO);
        // 2. Copy our vertices array in a buffer for OpenGL to use. 
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        //3. Then set our vertex attributes pointers. 
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Drawing code in the render loop. 
        //4. Draw the object. 
        glUseProgram(shaderProgramme);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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