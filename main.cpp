#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"
#include "Shader.h"

#include "Window.h"

int main(void) {
    std::vector<float> vertices = {
         0.5f,  0.5f,
         0.5f, -0.5f,
        -0.5f, -0.5f,
        -0.5f,  0.5f
    };
    std::vector<unsigned int> indices = {  
        0, 1, 3,
        1, 2, 3 
    };

    Crystal::Window window(640, 480, "Crystal-UI");
    Crystal::Shader shader("Shader/VertexShader.glsl", "Shader/FragmentShader.glsl");
    Crystal::Mesh rectangle(vertices, indices);

    std::vector<Crystal::Mesh*> meshes = { &rectangle };

    while(!window.ShouldClose()) {

        window.Render(shader, meshes);
        window.PollEvents();

    }

    glfwTerminate();
    return 0;
}