// TriangoloOpengl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Triangolo_OpenGL.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include "ShaderMaker.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

static unsigned int programId;

unsigned int VAO;
unsigned int VBO_G;
unsigned int VBO_C;
unsigned int EBO;

// Vertici del triangolo nel sistema di coordinate normalizzate

float vertices[] = {
	// posizioni         // colori
	-0.5f, -0.5f, 0.0f, // primo triangolo vertice in basso a sinistra
	0.5f, -0.5f, 0.0f,	// primo triangolo vertice in basso a destra
	0.5f, 0.5f, 0.0f,	// secondo triangolo vertice in basso a destra
	-0.5f, 0.5f, 0.0f	// secondo triangolo vertice in basso a sinistra
};

float colors[]{
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f};

int indices[] = {
	0, 1, 2, // primo triangolo
	0, 2, 3	 // secondo triangolo
};

void gestisci_shader(void)

{
	GLenum ErrorCheckValue = glGetError();

	char *vertexShader = (char *)"vertexShader.glsl";
	char *fragmentShader = (char *)"fragmentShader.glsl";

	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programId);
}

void INIT_VAO(void)
{
	// Genero un VAO
	glGenVertexArrays(1, &VAO);
	// Ne faccio il bind (lo collego, lo attivo)
	glBindVertexArray(VAO);

	// AL suo interno genero un VBO
	glGenBuffers(1, &VBO_G);
	// Ne faccio il bind (lo collego, lo attivo, assegnandogli il tipo GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, VBO_G);
	// Carico i dati vertices sulla GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Configurazione dell'attributo posizione: informo il vertex shader su: dove trova le informazioni sulle posizioni e come le deve leggere
	// dal buffer caricato sulla GPU
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// per gli indici
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// per i colori
	glGenBuffers(1, &VBO_C);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_C);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	glClearColor(1.0, 0.5, 0, 1.0);
}
void drawScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAO);
	// coglione cambialo
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// coglione ricordati
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Triangolo OpenGL");
	glutDisplayFunc(drawScene);

	glewExperimental = GL_TRUE;
	glewInit();
	gestisci_shader();
	INIT_VAO();

	glutMainLoop();
}
