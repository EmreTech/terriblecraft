#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../utils/types.hpp"

namespace gl
{

void resize_window_event(GLFWwindow *win, int width, int height)
{
    glViewport(0, 0, width, height);
}

struct Window
{
    GLFWwindow *window;

    Window(){}

    void init()
    {
        glfwInit();
        windowHints();

        // Open a window
        window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Voxel Game", NULL, NULL);
        if (!window)
        {
            std::cout << "Failed to create window with GLFW. You might not have the required OpenGL version" << '\n';
            quit();
            return;
        }

        glfwMakeContextCurrent(window);
        initGL();

        glfwSetFramebufferSizeCallback(window, resize_window_event);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void setTitle(const std::string& text)
    {
        glfwSetWindowTitle(window, text.c_str());
    }

    void quit()
    {
        glfwTerminate();
    }

    private:

    void windowHints()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
    #endif
    }

    void initGL()
    {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            std::cout << "Failed to initialize Glad (OpenGL)" << '\n';
            return;
        }
    }
};

} // namespace gl


#endif