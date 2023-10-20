#include "Lib.hpp"
#include "Window/Window.hpp"
#include "Shape/Shape.hpp"

#include <iostream>

#define PI 3.14159265358979323846

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

void buildCircle(float cx, float cy, float rx, float ry, Shape2D *shape)
{
    int i;
    float stepA = (2 * PI) / shape->getTriangleNum();
    float t, xx, yy;

    shape->addElementVertex(vec3(cx, cy, 0.0));
    shape->addElementColors(vec4(150.0 / 255.0, 75.0 / 255.0, 0.0, 0.2));

    for (i = 0; i <= shape->getTriangleNum(); i++)
    {
        t = (float)i * stepA;
        xx = cx + rx * cos(t);
        yy = cy + ry * sin(t);
        shape->addElementVertex(vec3(xx, yy, 0.0));
        // Colore
        shape->addElementColors(vec4(1.0, 0.0, 0.0, 1.0));
    }
    shape->setNumVertex(shape->getVertexArray().size());
}

int main()
{
    Window w = Window("Hello triangle", 800, 800);
    Shape2D shape = Shape2D(50);
    w.startWindow();
    // while (!glfwWindowShouldClose(this->window))
    // {
    //     // input
    //     this->processCloseInput();

    //     // render
    //     glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //     glClear(GL_COLOR_BUFFER_BIT);

    //     // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    //     glfwSwapBuffers(this->window);
    //     glfwPollEvents();
    // }
    shape.createVertexArray();

    return 0;
}
