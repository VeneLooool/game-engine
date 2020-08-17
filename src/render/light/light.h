#include "../../include.h"
#include "../shader.h"

struct t_dirLight 
{
public:
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

    void init_dirLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
};

struct t_pointLight
{
public:
    glm::vec3 position;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    void init_pointLight(glm::vec3 lightPos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
    void load_to_shader(Shader& shader, unsigned int curent_id);
};

struct t_spotLight
{
public:
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    void init_spotLight(glm::vec3 lightPos, glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 specul, float constan, float lin, float quad, float cutOf, float outerCutOf);
};
