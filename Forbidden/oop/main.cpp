#include <iostream>

#include "Window/Window.hpp"
#include "Shape/Shape.hpp"

#define PI 3.1415922625389

void buildCircle(float cx, float cy, float raggiox, float raggioy, Shape2D *fig)
{
    int i;
    float stepA = (2 * PI) / fig->getTriangleNum();
    float t, xx, yy;

    fig->addElementVertex(vec3(cx, cy, 0.0));

    fig->addElementColors(vec4(150.0 / 255.0, 75.0 / 255.0, 0.0, 0.2));

    for (i = 0; i <= fig->getTriangleNum(); i++)
    {
        t = (float)i * stepA;
        xx = cx + raggiox * cos(t);
        yy = cy + raggioy * sin(t);
        fig->addElementVertex(vec3(xx, yy, 0.0));
        fig->addElementColors(vec4(1.0, 0.0, 0.0, 1.0));
    }

    fig->setNumVertex(fig->getVertexArray().size());
}

int main()
{
    Window window = Window("Hello OOP World", 800, 800);
    window.startWindow();
    window.startRender();
    // window.createShader("vertexShader.glsl", "fragmentShader.glsl");
    // Shape2D shape = Shape2D(50);
    // buildCircle(0.0, 0.0, 1.0, 1.0, &shape);

    while (!glfwWindowShouldClose(window.getWindow()))
    {
        window.processCloseInput();

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    return 0;
}