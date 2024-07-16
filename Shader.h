#ifndef SHADER_H
#define SHADER_H

#include <string>

/* 
This class is a wrapper for the GLSL Vertex and Fragement Shader. It's purpose is to make 
working with shaders easier by providing a simple interface to set uniforms and use the shader.
*/

namespace Crystal {

    class Shader {
    public:
        Shader(const char* vertexSourceFile, const char* fragmentSourceFile);
        
        void Use();

        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;

    private:
        unsigned int ID;

        void CheckCompileErrors(unsigned int shader, std::string type);
    };

}

#endif
