#include "Rect.hpp"

Rect::Rect(float cx, float cy, float lenght)
{
	this->lenght = lenght;
	this->position = vec3(cx, cy, 0.0f);
	this->buildVertex();
}

void Rect::createVertexArray()
{
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vbo_g);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_g);
	glBufferData(GL_ARRAY_BUFFER, this->vertex.size() * sizeof(vec3), this->vertex.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(0);
}

void Rect::draw()
{
	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
