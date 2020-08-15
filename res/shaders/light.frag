#version 330 core
out vec4 color;	

struct Material {
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   float shininess;   
};

struct Light {
   vec3 position;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;

uniform Material material;
uniform Light light;

uniform vec3 viewPos;

void main()
{
    vec3 ambient = light.ambient * material.ambient;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = (diff * material.diffuse) * light.diffuse;

    vec3 viewDir  = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = (material.specular * spec) * light.specular;

    vec3 result = (ambient + diffuse + specular);
    color = vec4(result, 1.0f);
}