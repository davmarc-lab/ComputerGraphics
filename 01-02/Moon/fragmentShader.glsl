#version 420 core

// Interpolated values from the vertex shaders
// prende il vec4 color_frag dal file vertexShader.glsl
in vec4 color_frag;

out vec4 color;

void main() {
//Viene assegnato lo stesso colore ad ogni pixel
	color = color_frag;

}