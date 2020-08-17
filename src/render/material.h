#include "../include.h"

struct t_material
{
public:
	float link_shader;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	void load_material();
};