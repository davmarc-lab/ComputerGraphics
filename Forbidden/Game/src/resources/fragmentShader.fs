#version 330 core

in vec4 vertexColor;
out vec4 FragColor;

void main()
{
    FragColor = vertexColor;
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
