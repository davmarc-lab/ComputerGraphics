#include "Utils.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

Shape2D::Shape2D(int ntriangle, vector<vec3> vertex, vector<vec4> colors, mat4 model)
{
    this->ntriangle = ntriangle;
    this->vertex = vertex;
    this->colors = colors;
    this->model = model;
    this->nvertex = this->vertex.size();
}

Shape2D::Shape2D(int ntriangle)
{
    this->ntriangle = ntriangle;
}

/* Creates the VertexarrayObject and assign to the VertexBufferObject the vertex and colors values.
 */
void Shape2D::createVertexArray(int n)
{
    cout << this->vao << endl;
    /*
        Possibili problemi:
            - mancano le shader (ma non penso)
            - non trova la finestra e quindi non fa inizializzare il VAO
    */
    glGenVertexArrays(n, &(this->vao));
    cout << "Pass 1" << endl;
    glBindVertexArray(this->vao);
}

void Shape2D::drawShape2D(int n)
{
    glGenBuffers(n, &this->vbo_g);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_g);
    glBufferData(GL_ARRAY_BUFFER, this->vertex.size() * sizeof(vec3), this->vertex.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(n, &this->vbo_c);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_c);
    glBufferData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(vec4), this->colors.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(1);
}
