#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

class Window
{
private:
    GLFWwindow *window;
    int width;
    int height;
    string windowName;

public:
    Window(string windowName, int w, int h);
    int startWindow();
    void startRender();
    void startLoop();
    string getWindowName()
    {
        return windowName;
    }
};

/*
    This constructor creates a window with width w and height h
*/
Window::Window(string name, int w, int h)
{
    width = w;
    height = h;
    windowName = name;
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
    window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window." << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    return 0;
}

void Window::startRender()
{
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, updateFrameBufferSize);
}

void processCloseInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void Window::startLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        processCloseInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main()
{
    Window w = Window("Ciao", 200, 200);
    if (w.startWindow() < 0)
    {
        return -1;
    }
    w.startRender();
    w.startLoop();
    return 0;
}