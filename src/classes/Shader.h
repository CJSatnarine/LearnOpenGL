#ifndef SHADER_H
#define SHADER_H

#include "../glad/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
  public:
    // The Program ID.
    unsigned int ID;

    // Constructor that reads and builds the shader.
    Shader(const char *vertexPath, const char *fragmentPath);

    // Use or activate the shader.
    void Activate();

    // Deactivate or delete the shader.
    void Delete();

    // Utility uniform functions.
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

  private:
    // Error checking.
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
