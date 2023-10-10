//

#include <iostream>
#include "ShaderMaker.h"
#include "Lib.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
static unsigned int programId;

#define PI 3.14159265358979323846

typedef struct
{
	GLuint VAO;
	GLuint VBO_G;
	GLuint VBO_C;
	int nTriangles;
	// Vertici
	vector<vec3> vertici;
	vector<vec4> colors;
	// Numero vertici
	int nv;
	// Matrice di Modellazione: Traslazione*Rotazione*Scala
	mat4 Model;
} Figura;

Figura Farf = {}, Circle = {};
vector<Figura> scene;

mat4 Projection;
GLuint MatProj, MatModel;

int width = 1280, height = 720;
float scaling = 1.0f;
float dx = 0, dy = 0, w = 0, w2 = 0;

void crea_VAO_Vector(Figura *fig)
{

	glGenVertexArrays(1, &fig->VAO);
	glBindVertexArray(fig->VAO);
	// Genero , rendo attivo, riempio il VBO della geometria dei vertici
	glGenBuffers(1, &fig->VBO_G);
	glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_G);
	glBufferData(GL_ARRAY_BUFFER, fig->vertici.size() * sizeof(vec3), fig->vertici.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(0);

	// Genero , rendo attivo, riempio il VBO dei colori
	glGenBuffers(1, &fig->VBO_C);
	glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_C);
	glBufferData(GL_ARRAY_BUFFER, fig->colors.size() * sizeof(vec4), fig->colors.data(), GL_STATIC_DRAW);
	// Adesso carico il VBO dei colori nel layer 2
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(1);
}

void costruisci_farfalla(float cx, float cy, float raggiox, float raggioy, Figura *fig)
{

	int i;
	float stepA = (2 * PI) / fig->nTriangles;
	float t, xx, yy;

	fig->vertici.push_back(vec3(cx, cy, 0.0));

	fig->colors.push_back(vec4(150.0 / 255.0, 75.0 / 255.0, 0.0, 0.2));

	for (i = 0; i <= fig->nTriangles; i++)
	{
		t = (float)i * stepA;
		xx = cx + raggiox * (sin(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5));
		yy = cy + raggioy * (cos(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5));
		fig->vertici.push_back(vec3(xx, yy, 0.0));
		// Colore
		fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0)); // Nota che la quarta componente corrisponde alla trasparenza del colore
	}

	fig->nv = fig->vertici.size();
}

void costruisci_cerchio(float cx, float cy, float raggiox, float raggioy, Figura *fig)
{

	int i;
	float stepA = (2 * PI) / fig->nTriangles;
	float t, xx, yy;

	fig->vertici.push_back(vec3(cx, cy, 0.0));

	fig->colors.push_back(vec4(150.0 / 255.0, 75.0 / 255.0, 0.0, 0.2));

	for (i = 0; i <= fig->nTriangles; i++)
	{
		t = (float)i * stepA;
		xx = cx + raggiox * cos(t);
		yy = cy + raggioy * sin(t);
		fig->vertici.push_back(vec3(xx, yy, 0.0));
		// Colore
		fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0)); // Nota che la quarta componente corrisponde alla trasparenza del colore
	}

	fig->nv = fig->vertici.size();
}

void INIT_SHADER(void)
{
	GLenum ErrorCheckValue = glGetError();

	char *vertexShader = (char *)"vertexShader_mat.glsl";
	char *fragmentShader = (char *)"fragmentShader.glsl";

	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programId);
}

void INIT_VAO(void)
{
	Farf.nTriangles = 180;
	costruisci_farfalla(0.0, 0.0, 0.1, 0.1, &Farf);
	crea_VAO_Vector(&Farf);
	scene.push_back(Farf);

	Circle.nTriangles = 50;
	costruisci_cerchio(0.0, 0.0, 1.0, 1.0, &Circle);
	crea_VAO_Vector(&Circle);

	scene.push_back(Circle);

	Projection = ortho(0.0f, float(width), 0.0f, float(height));
	MatProj = glGetUniformLocation(programId, "Projection");
	MatModel = glGetUniformLocation(programId, "Model");
}

void drawScene(void)
{
	int k;
	float px = 400 + 200 * cos(w2);
	float py = 400 + 200 * sin(w2);

	glClearColor(0.0, 0.0, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	for (k = 0; k < scene.size(); k++)
	{
		if (k == 0)
		{
			scene[k].Model = mat4(1.0);
			// scene[k].Model = translate(scene[k].Model, vec3(1000.0 + dx, 350.0 + dy, 0.0));
			scene[k].Model = translate(scene[k].Model, vec3(px, py, 0.0));
			scene[k].Model = scale(scene[k].Model, vec3(300.0 * scaling, 300.0 * scaling, 1.0));
			scene[k].Model = rotate(scene[k].Model, radians(w), vec3(0, 0, 1));
		}
		else if (k == 1)
		{
			scene[k].Model = mat4(1.0);
			scene[k].Model = translate(scene[k].Model, vec3(400.0, 400.0, 0.0));
			scene[k].Model = scale(scene[k].Model, vec3(100.0 * scaling, 100.0 * scaling, 1.0));
		}

		glBindVertexArray(scene[k].VAO);
		glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
		glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(scene[k].Model));
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLE_FAN, 0, scene[k].nv);
		glBindVertexArray(0);
	}
	glutSwapBuffers();
}

void updateScale(int value)
{
	scaling = scaling * 1.1;
	if (scaling > 2)
		scaling = 1;

	glutTimerFunc(100, updateScale, 0);
	glutPostRedisplay();
}

void updateAngle(int value)
{
	w2 += 1;
	glutTimerFunc(250, updateAngle, 0);
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		dx -= 10;
		break;
	case 'd':
		dx += 10;
		break;
	case 'w':
		dy += 10;
		break;
	case 's':
		dy -= 10;
		break;
	case 'q':
		w += 5;
		break;
	case 'e':
		w -= 5;
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Farfalla OpenGL");
	glutDisplayFunc(drawScene);
	// glutKeyboardFunc(myKeyboard);
	glutTimerFunc(250, updateAngle, 0);

	glewExperimental = GL_TRUE;
	glewInit();
	INIT_SHADER();
	INIT_VAO();

	// Per gestire i colori con trasparenza: mescola i colori di geometrie hce si sovrappongono
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}
