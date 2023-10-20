#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>

class Window
{
private:
    GLFWwindow *window;
    int width;
    int height;
    const char *windowName;

    void processCloseInput();

public:
    Window(const char *windowName, int w, int h);
    int startWindow();
    void startRender();
    void startLoop();
    void closeWindow();
    char *getWindowName();
};