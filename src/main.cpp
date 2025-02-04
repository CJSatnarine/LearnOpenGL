#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

// Prototypes
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void renderingCommands(int VAO, int shaderProgram);

// Constants
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

// Shader source code.
const char *vertexShaderSource = "#version 330 core \n"
    "layout (location = 0) in vec3 aPos; \n"
    "void main() {\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
    "} \0";

const char *fragmentShaderSource = "#version 330 core \n"
    "out vec4 FragColour; \n"
    "void main() { \n"
    "FragColour = vec4(1.0f, 0.0f, 1.0f, 1.0f);"
    "} \0";

int main(void) {
  // Initialisation and configuration.
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // Create window.
  GLFWwindow *window =
      glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);

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

  // Vertex setup. 
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f, 
         0.0f,  0.5f, 0.0f
    };

    // Vertex Buffer Object.
    unsigned int vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
     
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);   // Create shader object. 
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);     // Attach shader object.
    glCompileShader(vertexShader);                                  // Compile shader object.
    
    // Fragment setup. 
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);// Create shader object. 
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // Attach shader object. 
    glCompileShader(fragmentShader);                                // Compile shader object. 

    // Shader program. 
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);                                    // Activate the shader program. 

    // Delete the shader objects no longer needed after linking them to the actual programme. 
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Linking vertex attributes. 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex Array Object. 
    unsigned int vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);

    // Initialisation code for the vertex array object.
    // Bind vertex array object.
    glBindVertexArray(vertexArrayObject);                            
    // Copy vertices array in a buffer for OpenGL to use.
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);                 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
    // Set vertex attribute pointers. 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    


  // Render loop.
  while (!glfwWindowShouldClose(window)) {
    // Input.
    processInput(window);

    // Rendering commands.
    renderingCommands(vertexArrayObject, shaderProgram);

    // Call events and swap buffers.
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

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

// Rendering commands function.
void renderingCommands(int VAO, int shaderProgram) {
  glClearColor(0.3f, 0.0f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
