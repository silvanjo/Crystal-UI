#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "Libs/glm/glm.hpp"

/* 
This class is a wrapper for the GLSL Vertex and Fragement Shader. It's purpose is to make 
working with shaders easier by providing a simple interface to set uniforms and use the shader.
*/

namespace Crystal {

    class Shader {
    public:
        Shader(const char* vertexSourceFile, const char* fragmentSourceFile);
        
        void Use();

        void SetBool(const std::string& name, bool value);
        void SetInt(const std::string& name, int value);
        void SetFloat(const std::string& name, float value);
        void SetVector4(const std::string& name, const glm::vec4& vector);
        void SetMatrix4(const std::string& name, const glm::mat4& matrix);

    private:
        unsigned int ID;

        void CheckCompileErrors(unsigned int shader, std::string type);
    };

}

#endif
