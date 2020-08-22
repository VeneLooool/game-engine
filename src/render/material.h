#include "../include.h"

struct t_material
{
public:
	unsigned int shaderID;
	string shader_name;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	void load_material();
};