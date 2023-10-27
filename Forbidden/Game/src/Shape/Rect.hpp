#pragma once

#include "../Lib.hpp"
#include <vector>

class Rect
{
private:
	GLuint vbo_g;
	GLuint ebo;
	vector<vec3> vertex;
	vector<vec4> colors;
	float lenght;
	mat4 model = mat4(1.0f);
	vec3 position;

	unsigned int indices[6] = {
		0, 1, 3, // first triangle
		1, 2, 3	 // second triangle
	};

	void buildVertex()
	{
		this->vertex.push_back(vec3(this->lenght / 2, this->lenght / 2, 0));   // top right corner
		this->vertex.push_back(vec3(this->lenght / 2, -this->lenght / 2, 0));  // bottom right corner
		this->vertex.push_back(vec3(-this->lenght / 2, -this->lenght / 2, 0)); // bottom left corner
		this->vertex.push_back(vec3(-this->lenght / 2, this->lenght / 2, 0));  // top left corner
	}

public:
	GLuint vao;

	Rect(float cx, float cy, float lenght);

	void createVertexArray();

	void draw();

	mat4 getModelMatrix() { return this->model; }

	void setModelMatrix(mat4 mod) { this->model = mod; }

	void scaleShape(vec3 mod) { this->model = scale(this->model, mod); }

	void translateShape(vec3 mod) { this->model = translate(this->model, mod); }

	void rotateShape(vec3 mod, float w) { this->model = rotate(this->model, radians(w), mod); }
};
