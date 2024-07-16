#include "Window.h"

#include <iostream>

namespace Crystal {

    Window::Window(int width, int height, const char* title) {
        this->width = width;
        this->height = height;

        if (!glfwInit()) {
            std::cout << "Failed to initialize GLFW" << std::endl;
            exit(-1);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window) {
            std::cout << "Failed to create window" << std::endl;
            glfwTerminate();
            exit(-1);
        }

        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK) {
            std::cout << "Failed to initialize GLEW" << std::endl;
            exit(-1);
        }
    }

    Window::~Window() {
        if (window) {
            glfwDestroyWindow(window);
        }
    }

    void Window::Render(Shader& shader, const std::vector<Mesh*>& meshes) {
        ClearCanvas();
        shader.Use();

        for (const auto& mesh : meshes) {
            mesh->Draw();
        }

        SwapBuffers();
    }

    bool Window::ShouldClose() {
        return glfwWindowShouldClose(window);
    }

    void Window::SwapBuffers() {
        glfwSwapBuffers(window);
    }

    void Window::PollEvents() {
        glfwPollEvents();
    }

    void Window::ClearCanvas() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::TerminateGLFW() {
        glfwTerminate();
    }

}