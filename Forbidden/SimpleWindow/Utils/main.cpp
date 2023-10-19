#include <iostream>
#include "Utils.hpp"
#include "Window.hpp"

using namespace std;

#define PI 3.14159265358979323846

void buildCircle(float cx, float cy, float rx, float ry, Shape2D* shape)
{
    int i;
    float stepA = (2 * PI) / shape->getTriangleNum();
    float t, xx, yy;

    shape->addElementVertex(vec3(cx, cy, 0.0));
    shape->addElementColors(vec4(150.0 / 255.0, 75.0 / 255.0, 0.0, 0.2));

    for (i = 0; i <= shape->getTriangleNum(); i++)
    {
    	t = (float)i * stepA;
	xx = cx + rx * cos(t);
	yy = cy + ry * sin(t);
        shape->addElementVertex(vec3(xx, yy, 0.0));
	// Colore
        shape->addElementColors(vec4(1.0, 0.0, 0.0, 1.0));
    }
    shape->setNumVertex(shape->getVertexArray().size());
}

int main(){
    Window window = Window("Hello OOP Circle", 800, 800);
    Shape2D f1 = Shape2D(50);

    buildCircle(0.0, 0.0, 1.0, 1.0, &f1);
    cout << f1.getVertexNum() << endl;
    
    // window.startWindow();
    // window.startRender();
    
    f1.createVertexArray(1);
    // f1.drawShape2D(1);
    
    // window.startLoop();

    return 0;
}
