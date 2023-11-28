//Gestione eventi tastiera per il movimento della telecamera
#include "Lib.h"
#include "geometria.h"
#include "Gestione_VAO.h"
#include "GestioneTelecamera.h"
#include "enum.h"
#include <cmath>
#include <glm/geometric.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/trigonometric.hpp>
#include <math.h>
extern bool visualizzaAncora;
extern int cont_cubi,cont_pir;
extern vector<Mesh> Scena;
extern string stringa_asse, Operazione;
extern vec3 asse;
extern mat4 Projection, View;
extern ViewSetup SetupTelecamera;
extern bool clickObject;
extern Mesh  Cubo, Piramide, Piano;
extern int selected_obj;
extern int height, width;
extern float raggio_sfera;
extern bool clickObject, moving_trackball;
extern int last_mouse_pos_X, last_mouse_pos_Y;
extern ViewSetup SetupTelecamera;
extern mat4 rotation_matrix;
void modifyModelMatrix(vec3 translation_vector, vec3 rotation_vector, GLfloat angle, GLfloat scale_factor)
{
    //ricordare che mat4(1) costruisce una matrice identità di ordine 4
    mat4 traslation = glm::translate(glm::mat4(1), translation_vector);
    mat4 scale = glm::scale(glm::mat4(1), glm::vec3(scale_factor, scale_factor, scale_factor));
    mat4 rotation = glm::rotate(glm::mat4(1), angle, rotation_vector);

    //Modifica la matrice di Modellazione dell'oggetto della scena selezionato postmolitplicando per le matrici scale*rotarion*traslation

    Scena[selected_obj].Model = Scena[selected_obj].Model * scale * rotation * traslation;

    glutPostRedisplay();

}
void keyboardPressedEvent(unsigned char key, int x, int y)
{
    char* intStr;
    string str;
    switch (key)
    {
        case 'a':
            moveCameraLeft();
            break;

        case 'd':
            moveCameraRight();
            break;


        case 'w':
            moveCameraForward();
            break;

        case 's':
            moveCameraBack();
            break;

        case 'v':  //Visualizzazione ancora
            visualizzaAncora = true;
            break;

        case 'g':  //Si entra in modalità di operazione traslazione
            OperationMode = TRASLATING;
            Operazione = "TRASLAZIONE";
            break;
        case 'r': //Si entra in modalità di operazione rotazione
            OperationMode = ROTATING;
            Operazione = "ROTAZIONE";
            break;
        case 'S':
            OperationMode = SCALING; //Si entra in modalità di operazione scalatura
            Operazione = "SCALATURA";
            break;
        case 27:
            glutLeaveMainLoop();
            break;
            // Selezione dell'asse
        case 'x':
            WorkingAxis = X;  //Seleziona l'asse X come asse lungo cui effettuare l'operazione selezionata (tra traslazione, rotazione, scalatura)
            stringa_asse = " Asse X";
            break;
        case 'y':
            WorkingAxis = Y;  //Seleziona l'asse Y come asse lungo cui effettuare l'operazione selezionata (tra traslazione, rotazione, scalatura)
            stringa_asse = " Asse Y";
            break;
        case 'z':
            WorkingAxis = Z;
            stringa_asse = " Asse Z";  //Seleziona l'asse Z come asse lungo cui effettuare l'operazione selezionata (tra traslazione, rotazione, scalatura)
            break;

        default:
            break;
    }

    // Selezione dell'asse per le trasformazioni
    switch (WorkingAxis) {
        case X:	asse = glm::vec3(1.0, 0.0, 0.0);

                break;
        case Y: asse = glm::vec3(0.0, 1.0, 0.0);

                break;
        case Z: asse = glm::vec3(0.0, 0.0, 1.0);

                break;
        default:
                break;
    }



    // I tasti + e -  aggiornano lo spostamento a destra o a sinistra, la rotazione in segno antiorario o in senso orario, la scalatura come amplificazione o diminuizione delle dimensioni

    float amount = .01;
    if (key == '+')
        amount *= 1;

    if (key == '-')
        amount *= -1;


    switch (OperationMode) {

        //la funzione modifyModelMatrix(glm::vec3 translation_vector, glm::vec3 rotation_vector, GLfloat angle, GLfloat scale_factor) 
        // definisce la matrice di modellazione che si vuole postmoltiplicare alla matrice di modellazione dell'oggetto selezionato, per poterlo traslare, ruotare scalare.

        case TRASLATING:
            // si passa angle 0 e scale factor =1, 
            modifyModelMatrix(asse * amount, asse, 0.0f, 1.0f);
            break;
        case ROTATING:
            // SI mette a zero il vettore di traslazione (vec3(0) e ad 1 il fattore di scale
            modifyModelMatrix(glm::vec3(0), asse, amount * 2.0f, 1.0f);
            break;
        case SCALING:
            // SI mette a zero il vettore di traslazione (vec3(0), angolo di rotazione a 0 e ad 1 il fattore di scala 1+amount.
            modifyModelMatrix(glm::vec3(0), asse, 0.0f, 1.0f + amount);
            break;



    }
    glutPostRedisplay();
}

void keyboardReleasedEvent(unsigned char key, int x, int y)
{
    {
        switch (key)
        {
            case 'v':
                visualizzaAncora = false;
                break;
            default:
                break;
        }
    }
    glutPostRedisplay();
}


vec3 get_ray_from_mouse(float mouse_x, float mouse_y) {

    mouse_y = height - mouse_y;

    // mappiamo le coordinate di viewport del mouse [0,width], [0,height] in coordinate normalizzate [-1,1]  
    float ndc_x = (2.0f * mouse_x) / width - 1.0;
    float ndc_y = (2.0f * mouse_y) / height - 1.0;
    float ndc_z = -1.0f;

    // Coordinate nel clip space 
    vec4 P_clip = vec4(ndc_x, ndc_y, ndc_z, 1.0);

    // Le coordinate Nell' eye space si ottengono premoltiplicando per l'inversa della matrice Projection.

    vec4 ViewModelp = inverse(Projection) * P_clip;

    // le coordinate nel world space: si ottengono premoltiplicando per l'inversa della matrice di Vista 
    ViewModelp.w = 1;
    vec4 Pw = inverse(View) * ViewModelp;
    vec3 ray_wor = normalize(vec3(Pw) - vec3(SetupTelecamera.position));

    return ray_wor;
}

/*controlla se un raggio interseca una sfera. In caso negativo, restituisce false. Rigetta
  le intersezioni dietro l'origine del raggio, e pone  intersection_distance all'intersezione p iù vicina.
  */

bool ray_sphere(vec3 O, vec3 d, vec3 sphere_centre_wor, float sphere_radius, float* intersection_distance) {

    //Calcoliamo O-C
    vec3 dist_sfera = O - sphere_centre_wor;
    float b = dot(dist_sfera, d);
    float cc = dot(dist_sfera, dist_sfera) - sphere_radius * sphere_radius;

    float delta = b * b - cc;

    if (delta < 0)  //Il raggio non interseca la sfera
        return false;
    //Calcolo i valori di t per cui il raggio interseca la sfera e restituisco il valore dell'intersezione 
    //più vicina all'osservatore (la t più piccola)
    if (delta > 0.0f) {
        //calcola le due intersezioni
        float t_a = -b + sqrt(delta);
        float t_b = -b - sqrt(delta);
        *intersection_distance = t_b;

        //Caso di intersezioni dietro l'osservatore
        if (t_a < 0.0) {
            if (t_b < 0)
                return false;
        }

        return true;
    }
    //Caso in cui il raggio è tangente alla sfera: un interesezione con molteplicità doppia.
    if (delta == 0) {
        float t = -b + sqrt(delta);
        if (t < 0)
            return false;
        *intersection_distance = t;
        return true;
    }

    return false;
}

void mouse(int button, int state, int x, int y)
{

    switch (button) {
        //Con il tasto sinistro premuto si attiva la modalità di trackball
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) { moving_trackball = true; }
            if (state == GLUT_UP) { moving_trackball = false; }
            //OperationMode = NAVIGATION;
            last_mouse_pos_X = x;
            last_mouse_pos_Y = y;
            break;

        case GLUT_RIGHT_BUTTON:

            //Con il tasto destro si selezionano gli oggetti nella scena
            if (state == GLUT_DOWN && glutGetModifiers() == GLUT_ACTIVE_CTRL)
            {
                float xmouse = x;
                float ymouse = y;
                vec3 ray_wor = get_ray_from_mouse(xmouse, ymouse);

                selected_obj = -1;
                float closest_intersection = 0.0f;
                for (int i = 0; i < Scena.size(); i++)
                {
                    float t_dist = 0.0f;

                    if (ray_sphere(SetupTelecamera.position, ray_wor, Scena[i].ancora_world, raggio_sfera, &t_dist))
                    {
                        if (selected_obj == -1 || t_dist < closest_intersection)
                        {
                            selected_obj = i;
                            closest_intersection = t_dist;
                        }
                    }
                }
                if (selected_obj > -1)
                    printf("Oggetto selezionato %d -> %s \n", selected_obj, Scena[selected_obj].nome.c_str());
            }
            break;
        default:
            break;
    }

    glutPostRedisplay();


}

glm::vec3 getTrackBallPoint(float x, float y)
{
    float ndcx = (2 * x - width) / width;
    float ndcy = (height - 2 * y) / height;

    float radicando = 1 - pow(x, 2) - pow(y, 2);
    return normalize(vec3(ndcx, ndcy, radicando > 0 ? sqrt(radicando) : 0));
}

void mouseActiveMotion(int x, int y)
{
    if (!moving_trackball)
        return;

    vec3 p1 = getTrackBallPoint(x, y);
    vec3 p2 = getTrackBallPoint(last_mouse_pos_X, last_mouse_pos_Y);

    float velocity = 1.0;
    float angle = acos(dot(p1, p2)) * velocity;
    vec3 rotation = normalize(cross(p1, p2));

    SetupTelecamera.direction = SetupTelecamera.position - SetupTelecamera.target;
    SetupTelecamera.position = SetupTelecamera.target + rotate(mat4(1.0f), radians(-angle), rotation) * SetupTelecamera.direction;

    glutPostRedisplay();

    last_mouse_pos_X = x;
    last_mouse_pos_Y = y;
}
