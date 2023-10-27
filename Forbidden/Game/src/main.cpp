#include "Lib.hpp"
#include "Window/Window.hpp"
#include "Shape/Shape.hpp"
#include "Shape/Rect.hpp"
#include "Shader/Shader.hpp"
#include "Scene/Scene.hpp"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

#define PI 3.14159265358979323846

const int WIDTH = 1280, HEIGHT = 724;
GLuint modelLoc;

void initWindowView(Shader shader)
{
    mat4 view = mat4(1.0f);
    mat4 projection = mat4(1.0f);
    view = translate(view, vec3(0.0f, 0.0f, 0.0f));
    // projection = perspective(radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f);
    view = translate(view, vec3(0, 0, -3));
    projection = ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT);
    GLuint viewLoc = glGetUniformLocation(shader.getId(), "view");
    GLuint projLoc = glGetUniformLocation(shader.getId(), "projection");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));
}

void buildRect(Shape2D *shape)
{
    shape->addElementVertex(vec3(-1, -1, 0));
    shape->addElementVertex(vec3(1, -1, 0));
    shape->addElementVertex(vec3(-1, 1, 0));
    shape->addElementVertex(vec3(1, 1, 0));

    shape->setVertexNum(4);
}

int main()
{
    Window w = Window("Hello rect", WIDTH, HEIGHT);
    if (w.initializeWindow() == 0)
    {
        Shader shader("resources/vertexShader.vs", "resources/fragmentShader.fs");

        Rect r = Rect(0, 0, 1);
        r.createVertexArray();

        Shape2D shape = Shape2D(4);
        buildRect(&shape);
        Scene scene = Scene();

        scene.addShape2dToScene(shape, GL_TRIANGLE_STRIP);
        shape.setModelMatrix(mat4(1.0f));

        shader.use();
        shape.setModelMatrix(translate(shape.getModelMatrix(), vec3(400, 400, 0.0)));
        shape.setModelMatrix(scale(shape.getModelMatrix(), vec3(WIDTH, HEIGHT, 1)));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(shape.getModelMatrix()));
        initWindowView(shader);

        while (!glfwWindowShouldClose(w.getWindow()))
        {
            // input
            w.processCloseInput();

            // render
            glClearColor(0.78f, 0.96f, 0.94f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



            glBindVertexArray(shape.getVertexArrayObject());
            glDrawArrays(GL_TRIANGLE_STRIP, 0, shape.getTriangleNum());
            glBindVertexArray(0);

            // swap buffers and poll IO events
            glfwSwapBuffers(w.getWindow());
            glfwPollEvents();
        }
        w.terminateWindow();
    }
    else
    {
        cout << "Cannot start the application, due to GLFW error" << endl;
        return -1;
    }

    return 0;
}
