#include <GLFW/glfw3.h>
#include <iostream>

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
void updateFrameBufferSize(GLFWwindow *window, int w, int h)
{
    glViewport(0, 0, w, h);
}

int Window::startWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    this->window = glfwCreateWindow(this->width, this->height, this->windowName, NULL, NULL);
    if (this->window == NULL)
    {
        cout << "Failed to create GLFW window." << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(this->window);
    return 0;
}

void Window::startRender()
{
    glViewport(0, 0, this->width, this->height);
    glfwSetFramebufferSizeCallback(this->window, updateFrameBufferSize);
}

void Window::processCloseInput()
{
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(this->window, true);
    }
}

void Window::startLoop()
{
    while (!glfwWindowShouldClose(this->window))
    {
        this->processCloseInput();

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}

char *Window::getWindowName()
{
    return (char *)this->windowName;
}

int main()
{
    const char *name = "Hello OOP World";
    Window w = Window(name, 500, 500);
    if (w.startWindow() < 0)
    {
        return -1;
    }
    w.startRender();
    w.startLoop();
    return 0;
}