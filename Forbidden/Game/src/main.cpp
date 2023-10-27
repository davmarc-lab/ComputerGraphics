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

int main()
{
    Window w = Window("Hello rect", WIDTH, HEIGHT);
    if (w.initializeWindow() == 0)
    {
        Shader shader("resources/vertexShader.vs", "resources/fragmentShader.fs");

        float vertices[] = {
            // positions          // texture coords
            0.5f, 0.5f, 0.0f,   // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f   // top left
        };
        unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        shader.use();

        // initWindowView(shader);

        while (!glfwWindowShouldClose(w.getWindow()))
        {
            // input
            w.processCloseInput();

            // render
            glClearColor(0.78f, 0.96f, 0.94f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            mat4 model = mat4(1.0f);
            model = translate(model, vec3(WIDTH / 2, HEIGHT / 2 - 100, 0));
            model = scale(model, vec3(WIDTH - 100, HEIGHT - 100, 1));
            shader.use();

            mat4 view = translate(view, vec3(0.0f, 0.0f, -3));
            mat4 projection = ortho(0.0f, (float)WIDTH, 0.0f, float(WIDTH));

            GLuint viewLoc = glGetUniformLocation(shader.getId(), "view");
            GLuint modelLoc = glGetUniformLocation(shader.getId(), "model");
            GLuint projLoc = glGetUniformLocation(shader.getId(), "projection");

            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
