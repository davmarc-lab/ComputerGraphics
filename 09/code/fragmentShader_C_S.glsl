#version 330 core
in vec4 ourColor;
out vec4 FragColor;  

in vec3 N, L, R, V;
uniform float time;
uniform vec2 resolution;
uniform int sceltaVS;

struct PointLight{
    vec3 position;
    vec3 color;
    float power;
};

//definizione di una varialie uniform che hala struttura PointLight
uniform PointLight light;
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
uniform Material material;

#define pi 3.14159235659
uniform sampler2D tex0;

in vec2 frag_coord_st;

void main()
{
    FragColor = vec4(ourColor);
}
