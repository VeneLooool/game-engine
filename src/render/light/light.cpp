#include "light.h"

void t_dirLight::init_dirLight(glm::vec3 direct, glm::vec3 ambi, glm::vec3 diff, glm::vec3 specul)
{
    direction = direct;
    ambient = ambi;
    diffuse = diff;
    specular = specul;
}

void t_pointLight::init_pointLight(glm::vec3 lightPos, glm::vec3 amb, glm::vec3 diff, glm::vec3 specul, float constan, float lin, float quad)
{
    position = lightPos;
    ambient = amb;
    diffuse = diff;
    specular = specul;
    constant = constan;
    linear = lin;
    quadratic = quad;
    
}

void t_pointLight::load_to_shader(Shader& shader, unsigned int curent_id)
{
    shader.setVec3(("pointLight[" + to_string(curent_id) + "].position"), position);
    shader.setVec3("pointLight[" + to_string(curent_id) + "].ambient", ambient);
    shader.setVec3("pointLight[" + to_string(curent_id) + "].diffuse", diffuse);
    shader.setVec3("pointLight[" + to_string(curent_id) + "].specular", specular);
    shader.setFloat("pointLight[" + to_string(curent_id) + "].constant", constant);
    shader.setFloat("pointLight[" + to_string(curent_id) + "].linear", linear);
    shader.setFloat("pointLight[" + to_string(curent_id) + "].quadratic", quadratic);
}

void t_spotLight::init_spotLight(glm::vec3 lightPos, glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 specul, float constan, float lin, float quad, float cutOf, float outerCutOf)
{
    position = lightPos;
    direction = dir;
    ambient = amb;
    diffuse = diff;
    specular = specul;
    constant = constan;
    linear = lin;
    quadratic = quad;

    cutOff = cutOf;
    outerCutOff = outerCutOf;
}
