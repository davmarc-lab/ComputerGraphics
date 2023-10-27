#pragma once

#include <vector>
#include <iostream>
#include "../Lib.hpp"

class Shape2D
{
private:
    GLuint vao;
    GLuint vbo_g;
    GLuint vbo_c;
    vector<vec3> vertex;
    vector<vec4> colors;
    int nvertex = 0;
    int ntriangle = 0;
    mat4 model;

public:
    Shape2D(int ntriangle, vector<vec3> vertex, vector<vec4> colors, mat4 model)
    {
        this->ntriangle = ntriangle;
        this->vertex = vertex;
        this->colors = colors;
        this->model = model;
        this->nvertex = this->vertex.size();
    }

    // Empty constructor
    Shape2D(int ntriangle)
    {
        this->ntriangle = ntriangle;
    }

    // Creates the VAO of the Shape2D
    void createVertexArray();

    // Create all vertex and color VBO, enable them and draw in the windows
    void drawShape2D(int n);

    // Add element to vertex vector3
    void addElementVertex(vec3 elem) { this->vertex.push_back(elem); }

    // Add element to colors vetcor4
    void addElementColors(vec4 elem)
    {
        this->colors.push_back(elem);
        // for (int i = 0; i < this->colors.size(); i++)
        // {
        //     cout << this->colors[i].r << ", " << this->colors[i].g << ", " << this->colors[i].b << endl;
        // }
    }

    // Retrieves the vertex number of the shape
    int getVertexNum() { return this->nvertex; }

    void setVertexNum(int n) { this->nvertex = n; }

    // Retrieves the triangles nummber of the shape
    int getTriangleNum() { return this->ntriangle; }

    void setTriangleNum(int n) { this->ntriangle = n; }

    vector<vec3> getVertexArray() { return this->vertex; }

    void setVertexArray(vector<vec3> vertex) { this->vertex = vertex; }

    void setColorsArray(vector<vec4> colors) { this->colors = colors; }

    mat4 getModelMatrix() { return this->model; }

    void setModelMatrix(mat4 model) { this->model = mat4(model); }

    GLuint getVertexArrayObject() { return this->vao; }

    vector<vec4> getColorsArray() { return this->colors; }
};
