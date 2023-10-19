#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

using namespace std;
using namespace glm;

class Shape2D
{
private:
    GLuint vao;
    GLuint vbo_g;
    GLuint vbo_c;
    vector<vec3> vertex;
    vector<vec4> colors;
    mat4 model;
public:
    Shape2D(vector<vec3> vertex, vector<vec4> colors, mat4 model);
    void createVertexArray(int n);
    void drawShape2D(int n);
};
