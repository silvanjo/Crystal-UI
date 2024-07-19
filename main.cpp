#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"
#include "Shapes.h"
#include "Shader.h"

#include "Window.h"

int main(void) {

    Crystal::Window window(640, 480, "Crystal-UI");
    Crystal::Shader shader("Shader/VertexShader.glsl", "Shader/FragmentShader.glsl");
    Crystal::Rectangle rectangle;

    std::vector<Crystal::Mesh*> meshes = { &rectangle };

    while(!window.ShouldClose()) {
        window.ClearCanvas();

        /* Rendering here */

        window.PollEvents();
        window.SwapBuffers();
    }

    glfwTerminate();
    return 0;
}