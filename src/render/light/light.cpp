#include "light.h"

void t_dirLight::init_dirLight(glm::vec3 direct, glm::vec3 ambi, glm::vec3 diff, glm::vec3 specul, glm::vec3 col)
{
    color = col;

    direction = direct;
    ambient = ambi;
    diffuse = diff;
    specular = specul;
}
void t_dirLight::load_to_shader(Shader& shader, unsigned int curent_id)
{
    shader.setVec3("dirLight.direction", direction);

    shader.setVec3("dirLight.ambient", ambient);
    shader.setVec3("dirLight.diffuse", diffuse);
    shader.setVec3("dirLight.specular", specular);
}

void t_pointLight::init_pointLight(glm::vec3 lightPos, glm::vec3 amb, glm::vec3 diff, glm::vec3 specul, float constan, float lin, float quad,glm::vec3 col)
{
    color = col;

    transform.position = lightPos;
    ambient = amb;
    diffuse = diff;
    specular = specul;
    constant = constan;
    linear = lin;
    quadratic = quad;
    
}

void t_pointLight::load_to_shader(Shader& shader, unsigned int curent_id)
{
    shader.setVec3(("pointLight[" + to_string(curent_id) + "].position"), transform.position);
    shader.setVec3("pointLight[" + to_string(curent_id) + "].ambient", ambient);
    shader.setVec3("pointLight[" + to_string(curent_id) + "].diffuse", diffuse);
    shader.setVec3("pointLight[" + to_string(curent_id) + "].specular", specular);
    shader.setFloat("pointLight[" + to_string(curent_id) + "].constant", constant);
    shader.setFloat("pointLight[" + to_string(curent_id) + "].linear", linear);
    shader.setFloat("pointLight[" + to_string(curent_id) + "].quadratic", quadratic);
}

void t_spotLight::init_spotLight(glm::vec3 lightPos, glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 specul, float constan, float lin, float quad, float cutOf, float outerCutOf, glm::vec3 col)
{
    color = col;

    transform.position = lightPos;
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

void t_spotLight::load_to_shader(Shader& shader, unsigned int curent_id)
{
    shader.setVec3("spotLight[" + to_string(curent_id) + "].direction", direction);

    shader.setVec3(("spotLight[" + to_string(curent_id) + "].position"), transform.position);
    shader.setVec3("spotLight[" + to_string(curent_id) + "].ambient", ambient);
    shader.setVec3("spotLight[" + to_string(curent_id) + "].diffuse", diffuse);
    shader.setVec3("spotLight[" + to_string(curent_id) + "].specular", specular);
    shader.setFloat("spotLight[" + to_string(curent_id) + "].constant", constant);
    shader.setFloat("spotLight[" + to_string(curent_id) + "].linear", linear);
    shader.setFloat("spotLight[" + to_string(curent_id) + "].quadratic", quadratic);

    shader.setFloat("spotLight[" + to_string(curent_id) + "].quadratic", cutOff);
    shader.setFloat("spotLight[" + to_string(curent_id) + "].quadratic", outerCutOff);
}


void t_light::add_dirLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
    t_dirLight dir;
    dir.ID = dirLight.size();
    dir.transform.position = position;
    dir.transform.rotation = rotation;
    dir.transform.scale = scale;
    dir.init_dirLight(direction, ambient, diffuse, specular, color);
    dirLight.push_back(dir);

}
void t_light::add_spotLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color, glm::vec3 lightPos, glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 specul, float constan, float lin, float quad, float cutOf, float outerCutOf)
{
    t_spotLight spot;
    spot.ID = spotLight.size();
    spot.transform.position = position;
    spot.transform.rotation = rotation;
    spot.transform.scale = scale;
    spot.init_spotLight(lightPos, dir, amb, diff, specul, constan, lin, quad, cutOf, outerCutOf, color);
    spotLight.push_back(spot);
}
void t_light::add_pointLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
{
    t_pointLight point;
    point.ID = pointLight.size();
    point.transform.position = position;
    point.transform.rotation = rotation;
    point.transform.scale = scale;
    point.init_pointLight(position, ambient, diffuse, specular, constant, linear, quadratic, color);
    pointLight.push_back(point);
}