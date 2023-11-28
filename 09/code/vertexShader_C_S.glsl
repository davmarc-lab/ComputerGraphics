#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec4 aColor; // the color variable has attribute position 1
layout (location = 2 ) in vec3 vertexNormal; // Attributo Normale 2



uniform mat4 Model;
uniform mat4 Projection;
uniform mat4 View;
uniform int sceltaVS;
uniform float time;
uniform vec3 viewPos;

//Struttura per la gestione di un punto luce

struct PointLight{
    vec3 position;
    vec3 color;
    float power;
};

//definizione di una variabile uniform che ha la struttura PointLight
uniform PointLight light;

//Struttura per la gestione di un materiale

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
uniform Material material;

out vec4 ourColor; // output a color to the fragment shader
out vec3 N,V,L,R;
float strenght=0.1;
void main()
{
    ourColor = aColor; // set ourColor to the input color we got from the vertex data

    gl_Position = Projection*View*Model*vec4(aPos, 1.0);

    if (sceltaVS == 1)
    {
        // Coordinate di vista
        vec4 eyePosition = View * Model * vec4(aPos, 1.0);

        // la luce è già in coordinate del mondo
        vec4 eyeLightPos = View * vec4(light.position, 1.0);
         
        N = normalize(transpose(inverse(mat3(View * Model))) * vertexNormal);
        V = normalize(viewPos - eyePosition.xyz);
        L = normalize((eyeLightPos - eyePosition).xyz);
        R = reflect(-L, N);

        // calcolo luce ambientale
        vec3 ambient = light.power * material.ambient;

        float cosTheta = max(dot(L, N), 0);
        vec3 diffuse = light.power * light.color * cosTheta * material.diffuse;

        // Speculare
        float cosAlpha = pow(max(dot(V, R), 0), material.shininess);
        vec3 specular = light.power * light.color * cosAlpha * material.specular;

        ourColor = vec4(ambient + diffuse + specular, 1.0);
    }
}  
