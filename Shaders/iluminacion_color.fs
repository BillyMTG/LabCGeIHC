#version 330 core

<<<<<<< HEAD
in vec3 our_normal;
in vec3 fragPos;

struct LightPosition{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec4 ourColor; 
uniform LightPosition light;
uniform vec3 viewPos;
=======
uniform vec4 ourColor; 
>>>>>>> 34e51efbe7a2de4def3fa3ce581d8224e196a9df
out vec4 color;

void main()
{
<<<<<<< HEAD
	vec3 ambient = light.ambient * vec3(ourColor);
	vec3 Normal = normalize(our_normal);
	vec3 lightDirection = normalize(light.position - fragPos);
	float diff = max(dot(Normal, lightDirection), 0.0);
	vec3 diffuse = diff * light.diffuse * vec3(ourColor);

	vec3 r = reflect(-lightDirection,Normal);
	vec3 viewDir = normalize(viewPos - fragPos);
	float spec = pow(max(dot(r, viewDir),0.0), 32.0);
	vec3 specular = spec * light.specular * vec3(ourColor);

	color = vec4(ambient + diffuse + specular, 1.0);
=======
    color = ourColor;
>>>>>>> 34e51efbe7a2de4def3fa3ce581d8224e196a9df
}
