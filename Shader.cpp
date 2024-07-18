#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

namespace Crystal {

    Shader::Shader(const char* vertexSourceFile, const char* fragmentSourceFile) {
        std::cout << "Creating shader with vertex source file: " << vertexSourceFile << " and fragment source file: " << fragmentSourceFile << std::endl;

        /* 1. Retrieve the vertex/fragment source code from filePath */
        std::string vertexCode;
        std::string fragmentCode;

        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        /* Ensure ifstream objects can throw exceptions: */
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            /* Open shader files */
            vShaderFile.open(vertexSourceFile);
            fShaderFile.open(fragmentSourceFile);

            std::stringstream vShaderStream, fShaderStream;

            /* Read file's buffer contents into streams */
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            
            /* Close file handlers */
            vShaderFile.close();
            fShaderFile.close();

            /* Convert stream into string */
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();

        } catch (std::ifstream::failure e) {
            std::cout << "Error occured when parsing shaders." << std::endl;
            std::cout << e.what() << std::endl;
        }

        const char* vertexShaderCode = vertexCode.c_str();
        const char* fragmentShaderCode = fragmentCode.c_str();

        /* Compile shaders */
        unsigned int vertexShader, fragmentShader;

        /* Vertex shader */
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
        glCompileShader(vertexShader);
        CheckCompileErrors(vertexShader, "VERTEX");

        /* Fragment Shader */
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
        glCompileShader(fragmentShader);
        CheckCompileErrors(fragmentShader, "FRAGMENT");

        /* Shader Program */
        this->ID = glCreateProgram();
        glAttachShader(this->ID, vertexShader);
        glAttachShader(this->ID, fragmentShader);
        glLinkProgram(this->ID);
        CheckCompileErrors(this->ID, "PROGRAM");

        /* Shaders can now be deleted */
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Shader::Use() {
        glUseProgram(this->ID);
    }

    void Shader::SetBool(const std::string& name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
    }

    void Shader::SetInt(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::SetFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::CheckCompileErrors(unsigned int shader, std::string type) {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }

}