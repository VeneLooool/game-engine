#include "../../include.h"
#include "../model.h"

class t_dirLight 
{
public:
    unsigned int ID;
    t_transform transform;

	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

    void init_dirLight(glm::vec3 direct, glm::vec3 ambi, glm::vec3 diff, glm::vec3 specul);
    void load_to_shader(Shader& shader, unsigned int curent_id);
};

class t_pointLight
{
public:
    unsigned int ID;
    t_transform transform;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float range;

    void init_pointLight(glm::vec3 lightPos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
    void load_to_shader(Shader& shader, unsigned int curent_id);
};

class t_spotLight
{
public:
    unsigned int ID;
    t_transform transform;

    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float range;

    void init_spotLight(glm::vec3 lightPos, glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 specul, float constan, float lin, float quad, float cutOf, float outerCutOf);
    void load_to_shader(Shader& shader, unsigned int curent_id);
};

class t_light
{
public:
    vector<t_dirLight> dirLight;
    vector<t_spotLight> spotLight;
    vector<t_pointLight> pointLight;

    void add_dirLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    void add_spotLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 lightPos, glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 specul, float constan, float lin, float quad, float cutOf, float outerCutOf);
    void add_pointLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
};
