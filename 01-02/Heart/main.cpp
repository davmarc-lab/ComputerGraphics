// TriangoloOpengl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Triangolo_OpenGL.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include "ShaderMaker.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>

#define PI 3.1415922625389

static unsigned int programId;

unsigned int VAO;
unsigned int VBO_G;

typedef struct
{
	float x, y, z, r, g, b, a;
} Point;

int nPoints = 80;
// centerVertex + nTringles + lastVertex
int nVertex = nPoints + 2;
Point *vertices = new Point[nVertex];

void build_circle(float cx, float cy, float rx, float ry, Point *circle)
{
	int cont = 0;
	float step = (2 * PI) / nPoints;
	double thetai;
	circle[cont].x = cx;
	circle[cont].y = cy;
	circle[cont].z = 0.0;
	circle[cont].r = 1.0;
	circle[cont].g = 1.0;
	circle[cont].b = 1.0;
	circle[cont].a = 1.0;
	cont++;

	for (int i = 0; i <= nPoints; i++)
	{
		thetai = i * step;
		circle[cont].x = cx + (16 * pow(sin(thetai), 3.0)) * rx;
		circle[cont].y = cy + (13 * cos(thetai) - 5 * cos(2 * thetai) - 2 * cos(3 * thetai) - cos(4 * thetai)) * ry;
		circle[cont].z = 0.0;
		circle[cont].r = 1.0;
		circle[cont].g = 0.0;
		circle[cont].b = 0.0;
		circle[cont].a = 1.0;
		cont++;
	}
}

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
	build_circle(0, 0, 0.06, 0.06, vertices);
	// Genero un VAO
	glGenVertexArrays(1, &VAO);
	// Ne faccio il bind (lo collego, lo attivo)
	glBindVertexArray(VAO);

	// AL suo interno genero un VBO
	glGenBuffers(1, &VBO_G);
	// Ne faccio il bind (lo collego, lo attivo, assegnandogli il tipo GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, VBO_G);
	// Carico i dati vertices sulla GPU
	glBufferData(GL_ARRAY_BUFFER, nVertex * sizeof(Point), &vertices[0], GL_STATIC_DRAW);

	// Configurazione dell'attributo posizione: informo il vertex shader su: dove trova le informazioni sulle posizioni e come le deve leggere
	// dal buffer caricato sulla GPU
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glClearColor(0.0, 0.0, 0, 1.0);
}
void drawScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(4.0);
	glBindVertexArray(VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLE_FAN, 0, nVertex);

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(500, 450);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Triangolo OpenGL");
	glutDisplayFunc(drawScene);

	glewExperimental = GL_TRUE;
	glewInit();
	gestisci_shader();
	INIT_VAO();

	glutMainLoop();
}
