//Movimento della telecamera
#include "Lib.h"
#include "Strutture.h"
extern ViewSetup SetupTelecamera;
extern float cameraSpeed;
extern int height, widht;
extern bool firstMouse;
extern float lastX, lastY,Theta, Phi;
void moveCameraForward()
{

}


void moveCameraBack()
{

	 
}

void moveCameraLeft()
{
 
}

void moveCameraRight()
{
 
}

 

void my_passive_mouse(int xpos, int ypos)
{


	float alfa = 0.05; //serve ridimensionare l'offset tra due posizioni successive del mosue
	ypos = height - ypos;
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	xoffset *= alfa;
	yoffset *= alfa;
	Theta += xoffset;   //Aggiorno l'angolo Theta sommandogli l'offset della posizione x del mouse
	Phi += yoffset;  //Aggiorno l'angolo Phi sommandogli l'offset della posizione y del mouse 

	// Facciamo si' che l'angolo di Phi vari tra -90 e 90.
	if (Phi > 89.0f)
		Phi = 89.0f;
	if (Phi < -89.0f)
		Phi = -89.0f;

	//Ricavo le coordinate x,y,z del punto che sulla sfera individuato dagli angoli Theta e Phi  //TO DO 
	vec3 front;
 

	glutPostRedisplay();
}

