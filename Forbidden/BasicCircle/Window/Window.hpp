#pragma once

#include <string.h>
#include "../Lib.hpp"

class Window
{
private:
    GLFWwindow *window;
    int width;
    int height;
    const char *windowName;

public:
    Window(const char *windowName, int w, int h);

    int startWindow();

    void startRender();

    void closeWindow();

    void processCloseInput();

    char *getWindowName() { return (char *)this->windowName; };

    GLFWwindow *getWindow() { return this->window; };

    // void createShader(string vertexShader, string fragmentShader);
};