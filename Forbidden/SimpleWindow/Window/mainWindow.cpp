#include <iostream>
#include <GLFW/glfw3.h>

#include "Window.hpp"

const unsigned int width = 800;
const unsigned int height = 600;
const char *windowName = "Hello OOP World";

int main()
{
    Window w = Window(windowName, 500, 500);
    if (w.startWindow() < 0)
    {
        return -1;
    }
    w.startRender();
    w.startLoop();
    return 0;
}
