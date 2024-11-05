#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader {
    public: 
    unsigned int ID;

    // Constructor reads and builds the shader. 
    Shader(const char* vertexPath, const char* fragmentPath) {
        // 1. Retrieve vertex and fragment source code from file path. 
        string vertexCode;
        string fragmentCode;
        ifstream vShaderFile;
        ifstream fShaderFile;

        // Ensure ifstream objects throw exceptions. 
        vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
        fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
        try {
            // Open files. 
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            
            stringstream vShaderStream, fShaderStream;

            // Read file buffer contents into streams.
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // Choose file handlers.
            vShaderFile.close();
            fShaderFile.close();

            // Convert stream into string. 
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str(); 
        } catch (ifstream::failure e) {
            cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // 2. Compile Shaders. 
        unsigned int vertex;
        unsigned int fragment; 
        int success;
        char infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);

        // Print errors. 
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
        }

        fragment = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);

        // Print errors. 
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
        }

        // Shader programme. 
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        // Print errors. 
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
        }

        // Delete shaders as they are no longer needed after linking. 
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    // Use/activate the shader. 
    void use() {
        glUseProgram(ID);
    }
    
    // Utility uniform functions. 
    void setBool(const string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
    }

    void setInt(const string &name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const string &name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);     
    }
};

#endif