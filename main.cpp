#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"
#include "Shapes.h"
#include "Shader.h"
#include "Button.h"

#include "Window.h"

int main(void) {

    Crystal::Window window(640, 480, "Crystal-UI");
    Crystal::Shader shader("Shader/VertexShader.glsl", "Shader/FragmentShader.glsl");

    Crystal::Button button(std::shared_ptr<Crystal::Component>(), 0.5f, 0.2f, 0.f, 0.f, true);

    while(!window.ShouldClose()) {
        window.ClearCanvas();

        shader.Use();
        /* Rendering here */
        button.Render(shader);

        window.PollEvents();
        window.SwapBuffers();
    }

    glfwTerminate();
    return 0;
}