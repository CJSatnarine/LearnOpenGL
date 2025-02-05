#include "Shader.h"
#include <sstream>

using namespace std;

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
  // Retreive the vertex/fragment source code from the filepath.
  string vertexCode;
  string fragmentCode;
  ifstream vertexShaderFile;
  ifstream fragmentShaderFile;

  // Ensure ifstream objects can throw exceptions.
  vertexShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
  fragmentShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        // Open files. 
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);

        stringstream vertexShaderStream;
        stringstream fragmentShaderStream;

        // Read file's buffer contents into streams.
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        // Close the file handlers. 
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // Convert the stream into string. 
        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();

    } catch(std::ifstream::failure e) {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }

  // Compile Shaders.
  const char *vertexShaderCode = vertexCode.c_str();
  const char *fragmentShaderCode = fragmentCode.c_str();
  unsigned int vertex, fragment;

  // Vertex shader.
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexShaderCode, NULL);
  glCompileShader(vertex);
  checkCompileErrors(vertex, "VERTEX");

  // Fragment Shaders.
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
  glCompileShader(fragment);
  checkCompileErrors(fragment, "FRAGMENT");

  // Shader Program.
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  checkCompileErrors(ID, "PROGRAM");

  // Shaders no longer needed after linking.
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use() { glUseProgram(ID); }

void Shader::setBool(const string &name, bool value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const string &name, int value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const string &name, float value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::checkCompileErrors(unsigned int shader, string type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
           << infoLog
           << "\n -- --------------------------------------------------- -- "
           << endl;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
           << infoLog
           << "\n -- --------------------------------------------------- -- "
           << endl;
    }
  }
} 
