#include "../include.h"

struct t_material
{
	float link_shader;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};