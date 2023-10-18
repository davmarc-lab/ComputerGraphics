#include <iostream>
#include <GLFW/glfw3.h>

const unsigned int width = 800;
const unsigned int height = 600;
const char *windowName = "Hello World";

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processCloseInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    // instanciate the window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, windowName, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window. Closing application." << std::endl;
        glfwTerminate();
        return -1;
    }
    // focusing the window jsut created
    glfwMakeContextCurrent(window);
    // resizing render area everytime window get resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // render area
    glViewport(0, 0, width, height);
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // process the default input on window
        processCloseInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // clear all the GLFW window
    glfwTerminate();
    return 0;
}
