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

    Crystal::Button button_red(std::shared_ptr<Crystal::Component>(), .2f, .4f, -0.5f, -0.5f, true);
    Crystal::Button button_green(std::shared_ptr<Crystal::Component>(), .2f, .4f, 0.5f, -0.5f, true);
    Crystal::Button button_blue(std::shared_ptr<Crystal::Component>(), .2f, .4f, 0.5f, 0.5f, true);
    button_red.SetColor(1.f, 0.f, 0.f, 1.f);
    button_green.SetColor(0.f, 1.f, 0.f, .5f);
    button_blue.SetColor(0.f, 0.f, 1.f, .1f);

    while(!window.ShouldClose()) {
        window.ClearCanvas();

        shader.Use();

        /* Rendering here */
        button_red.Render(shader);
        button_green.Render(shader);
        button_blue.Render(shader);

        window.PollEvents();
        window.SwapBuffers();
    }

    glfwTerminate();
    return 0;
}