#ifndef CRYSTAL_WINDOW_H
#define CRYSTAL_SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Mesh.h"
#include "Shader.h"

namespace Crystal {

    class Window {
    public:
        Window(int width, int height, const char* title);
        ~Window();

        bool ShouldClose();
        void SwapBuffers();
        void PollEvents();
        void ClearCanvas();
        void TerminateGLFW();

    private:
        GLFWwindow* window;
        int width, height;
    };

}

#endif