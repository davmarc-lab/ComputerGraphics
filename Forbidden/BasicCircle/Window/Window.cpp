#include <iostream>
#include <string.h>
#include "Window.hpp"

using namespace std;

/*
    This constructor creates a window with width w and height h
*/
Window::Window(const char *name, int w, int h)
{
    this->width = w;
    this->height = h;
    this->windowName = name;
}

/*
    Update vieport dimension, usually used after resize window event
*/
void framebuffer_size_callback(GLFWwindow *window, int w, int h)
{
    glViewport(0, 0, w, h);
}

int Window::startWindow()
{
    //
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //
    this->window = glfwCreateWindow(this->width, this->height, this->windowName, NULL, NULL);
    if (this->window == NULL)
    {
        cout << "Failed to create GLFW window." << endl;
        glfwTerminate();
        return -1;
    }
    //
    glfwMakeContextCurrent(this->window);
    glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
    //
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -2;
    }
    return 0;
}

void Window::closeWindow()
{
    // delete all vao, vbo, ebo arrays
    glfwSetWindowShouldClose(this->window, true);
}

void Window::processCloseInput()
{
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        this->closeWindow();
    }
}

// void Window::createShader(string vertexShader, string fragmentShader)
// {
//     // GLenum ErrorCheckValue = glGetError();
//     // int programId = ShaderReader::createProgram((char *)vertexShader.c_str(), (char *)fragmentShader.c_str());
//     // glUseProgram(programId);
// }
