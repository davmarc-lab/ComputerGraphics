#include <iostream>

#include "ShaderMaker.h"
#include "Lib.h"
#include "geometria.h"
#include "Gestione_VAO.h"
#include "GestioneTesto.h"
#include "inizializzazioni.h"
#include "GestioneInterazioni.h"
#include "GestioneTelecamera.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//Inizializzazione Booleano per la visualizzazione dell'ancora
bool visualizzaAncora =false;
int last_mouse_pos_Y;
int last_mouse_pos_X;
bool moving_trackball = 0;
float angolo;
//Impostazione larghezza ed altezza della finestra sullo schermo
int width = 1024;
int height = 800;
//Definizione stringhe da visualizzare sulla finestra
string stringa_asse;
string Operazione;
vector<Material> materials;
vector<Shader> shaders;
LightShaderUniform light_unif = {};

 int w_up = width;
int h_up = height;
mat4 Projection_text;
mat4 rotation_matrix = mat4(1.0);

unsigned int programId, programId_text, MatrixProj, MatrixProj_txt, MatModel, MatView, locSceltaVs,loctime;
unsigned int loc_view_pos, locSceltaFs, VAO_Text, VBO_Text;
float raggio_sfera=2.5;
vec3 asse = vec3(0.0, 1.0, 0.0);
int selected_obj = 0;
bool clickObject = true;
float cameraSpeed = 0.1;
 vector<Mesh> Scena, Snowman;
 point_light light;

 //Definzione SetupTelecamera e SetupProspettiva

 ViewSetup SetupTelecamera;
 PerspectiveSetup SetupProspettiva;

//Varibili per la gestione della direzione della telecamera tramite mouse
bool firstMouse = true;
float lastX = (float)width / 2;
float lastY = (float)height / 2;
float Theta = -90.0f;
float Phi = 0.0f;


mat4 Projection, Model, View;

void resize(int w, int h)
{
	//Imposto la matrice di Proiezione per il rendering del testo

	Projection_text = ortho(0.0f, (float)width, 0.0f, (float)height);

	//Imposto la matrice di proiezione per la scena da diegnare
	Projection = perspective(radians(SetupProspettiva.fovY),SetupProspettiva.aspect, SetupProspettiva.near_plane, SetupProspettiva.far_plane);

	float AspectRatio_mondo = (float)(width) / (float)(height); //Rapporto larghezza altezza di tutto ciò che è nel mondo
	 //Se l'aspect ratio del mondo è diversa da quella della finestra devo mappare in modo diverso 
	 //per evitare distorsioni del disegno
	if (AspectRatio_mondo > w / h)   //Se ridimensioniamo la larghezza della Viewport
	{
		glViewport(0, 0, w, w / AspectRatio_mondo);
		w_up = (float)w;
		h_up = w / AspectRatio_mondo;
	}
	else {  //Se ridimensioniamo la larghezza della viewport oppure se l'aspect ratio tra la finestra del mondo 
			//e la finestra sullo schermo sono uguali
		glViewport(0, 0, h * AspectRatio_mondo, h);
		w_up = h * AspectRatio_mondo;
		h_up = (float)h;
	}
}


void main_menu_func(int option)
{
	switch (option)
	{
	case MenuOption::WIRE_FRAME: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case MenuOption::FACE_FILL: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;


	default:
		break;
	}
	glutPostRedisplay();
}

void material_menu_function(int option)
{
	if (selected_obj > -1)
	Scena[selected_obj].material = (MaterialType)option;
	printf("Scena[selected_obj].material %f %f %f", Scena[selected_obj].material);
	glutPostRedisplay();
}

void shader_menu_function(int option) {
	if (selected_obj > -1)
		Scena[selected_obj].sceltaVS = shaders[option].value;

	glutPostRedisplay();
}

void buildOpenGLMenu()
{
	int materialSubMenu = glutCreateMenu(material_menu_function);

	glutAddMenuEntry(materials[MaterialType::EMERALD].name.c_str(), MaterialType::EMERALD);
	glutAddMenuEntry(materials[MaterialType::BRASS].name.c_str(), MaterialType::BRASS);
	glutAddMenuEntry(materials[MaterialType::SLATE].name.c_str(), MaterialType::SLATE);
	glutAddMenuEntry(materials[MaterialType::YELLOW].name.c_str(), MaterialType::YELLOW);

	int shaderSubMenu = glutCreateMenu(shader_menu_function);
	glutAddMenuEntry(shaders[ShaderOption::NONE].name.c_str(), ShaderOption::NONE);
	glutAddMenuEntry(shaders[ShaderOption::GOURAD_SHADING].name.c_str(), ShaderOption::GOURAD_SHADING);
	glutAddMenuEntry(shaders[ShaderOption::PHONG_SHADING].name.c_str(), ShaderOption::PHONG_SHADING);
	

	glutCreateMenu(main_menu_func); // richiama main_menu_func() alla selezione di una voce menu
	glutAddMenuEntry("Opzioni", -1); //-1 significa che non si vuole gestire questa riga
	glutAddMenuEntry("", -1);
	glutAddMenuEntry("Wireframe", MenuOption::WIRE_FRAME);
	glutAddMenuEntry("Face fill", MenuOption::FACE_FILL);
	glutAddSubMenu("Material", materialSubMenu);
	glutAddSubMenu("Shader", shaderSubMenu);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

void drawScene(void)
{
	int i, j,k;
	float traslax, traslay;

	//Utilizzo il program shader per il disegno

	glUseProgram(programId);

	glUniformMatrix4fv(MatrixProj, 1, GL_FALSE, value_ptr(Projection));

	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;

	glClearColor(0.0, 0.0, 0.0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	  
	 
	//Costruisco la matrice di Vista che applicata ai vertici in coordinate del mondo li trasforma nel sistema di riferimento della camera.
	View = lookAt(vec3(SetupTelecamera.position), vec3(SetupTelecamera.target), vec3(SetupTelecamera.upVector));

	//Passo al Vertex Shader il puntatore alla matrice View, che sarà associata alla variabile Uniform mat4 Projection
   //all'interno del Vertex shader. Uso l'identificatio MatView
	glPointSize(10.0);
	glUniformMatrix4fv(MatView, 1, GL_FALSE, value_ptr(View));
	//Definizione colore luce, posizione ed intensit 
	glUniform3f(light_unif.light_position_pointer, light.position.x + 80 * cos(radians(angolo)), light.position.y, light.position.z + 80 * sin(radians(angolo)));
	glUniform3f(light_unif.light_color_pointer, light.color.r, light.color.g, light.color.b);
	glUniform1f(light_unif.light_power_pointer, light.power);

	//Passo la posizione della camera
	glUniform3f(loc_view_pos, SetupTelecamera.position.x, SetupTelecamera.position.y, SetupTelecamera.position.z);
	glUniform1f(loctime, time);
	for (int k = 0; k < Scena.size(); k++)
	{

		//Trasformazione delle coordinate dell'ancora dal sistema di riferimento dell'oggetto in sistema
		//di riferimento del mondo premoltiplicando per la matrice di Modellazione.

		Scena[k].ancora_world = Scena[k].ancora_obj;
		Scena[k].ancora_world = Scena[k].Model * Scena[k].ancora_world;
		//Passo al Vertex Shader il puntatore alla matrice Model dell'oggetto k-esimo della Scena, che sarà associata alla variabile Uniform mat4 Projection
		//all'interno del Vertex shader. Uso l'identificatio MatModel
		glUniform1i(locSceltaVs, Scena[k].sceltaVS);
	 
		glUniform3fv(light_unif.material_ambient, 1, glm::value_ptr(materials[Scena[k].material].ambient));
		glUniform3fv(light_unif.material_diffuse, 1, glm::value_ptr(materials[Scena[k].material].diffuse));
		glUniform3fv(light_unif.material_specular, 1, glm::value_ptr(materials[Scena[k].material].specular));
		glUniform1f(light_unif.material_shininess, materials[Scena[k].material].shininess);
		glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Scena[k].Model));
		glBindVertexArray(Scena[k].VAO);
		
	 	if (visualizzaAncora==true)
		{
			//Visualizzo l'ancora dell'oggetto
			int ind = Scena[k].indici.size() - 1;

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, BUFFER_OFFSET(ind * sizeof(GLuint)));
		}
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, (Scena[k].indici.size() - 1) * sizeof(GLuint), GL_UNSIGNED_INT, 0);

	 
		glBindVertexArray(0);

	}


	//Imposto il renderizzatore del testo



	RenderText(programId_text, Projection_text, Operazione, VAO_Text, VBO_Text, 50.0f, 650.0f, 0.5f, glm::vec3(1.0, 0.0f, 0.2f));

	RenderText(programId_text, Projection_text, stringa_asse, VAO_Text, VBO_Text, 50.0f, 700.0f, 0.5f, glm::vec3(1.0, 0.0f, 0.2f));


	RenderText(programId_text, Projection_text, "Oggetto selezionato", VAO_Text, VBO_Text, 80.0f, 750.0f, 0.5f, glm::vec3(1.0, 0.0f, 0.2f));

	if (selected_obj > -1)
		RenderText(programId_text, Projection_text, Scena[selected_obj].nome.c_str(), VAO_Text, VBO_Text, 120.0f, 700.0f, 0.5f, glm::vec3(1.0, 0.0f, 0.2f));


	glutSwapBuffers();

}


void update(int value)
{ 
	angolo = angolo + 1;
	glutTimerFunc(200, update, 0);
	glutPostRedisplay();

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);


	//Inizializzo finestra per il rendering della scena 3d con tutti i suoi eventi le sue inizializzazioni e le sue impostazioni

	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Scena 3D");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);

	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboardPressedEvent);
	glutKeyboardUpFunc(keyboardReleasedEvent);
	glutTimerFunc(200, update, 0);
	//glutPassiveMotionFunc(my_passive_mouse);
	glutMotionFunc(mouseActiveMotion);
	glewExperimental = GL_TRUE;
 
	//Inizializzazioni
	glewInit();
	INIT_SHADER();
	INIT_VAO();
	INIT_CAMERA_PROJECTION();
	INIT_Illuminazione();
	INIT_VAO_Text();
	buildOpenGLMenu();
	Init_Freetype();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	
	//Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 Projection (in vertex shader).
	//QUesto identificativo sarà poi utilizzato per il trasferimento della matrice Projection al Vertex Shader
	MatrixProj = glGetUniformLocation(programId, "Projection");
	//Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 Model (in vertex shader)
	//QUesto identificativo sarà poi utilizzato per il trasferimento della matrice Model al Vertex Shader
	MatModel = glGetUniformLocation(programId, "Model");
	//Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 View (in vertex shader)
	//QUesto identificativo sarà poi utilizzato per il trasferimento della matrice View al Vertex Shader
	MatView = glGetUniformLocation(programId, "View");

	locSceltaVs = glGetUniformLocation(programId, "sceltaVS");
	locSceltaFs = glGetUniformLocation(programId, "sceltaFS");
	loctime= glGetUniformLocation(programId, "time");
	loc_view_pos = glGetUniformLocation(programId, "ViewPos");

	

	light_unif.light_position_pointer = glGetUniformLocation(programId, "light.position");
	light_unif.light_color_pointer = glGetUniformLocation(programId, "light.color");
	light_unif.light_power_pointer = glGetUniformLocation(programId, "light.power");
	light_unif.material_ambient = glGetUniformLocation(programId, "material.ambient");
	light_unif.material_diffuse = glGetUniformLocation(programId, "material.diffuse");
	light_unif.material_specular = glGetUniformLocation(programId, "material.specular");
	light_unif.material_shininess = glGetUniformLocation(programId, "material.shininess");	
	glutMainLoop();
}

