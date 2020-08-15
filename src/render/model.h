#include "shader.h"
#include "material.h"
#include "../include.h"

struct  t_vertex
{
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 text;
};

struct t_texture 
{
	unsigned int id;
	string type;
};

struct t_model
{


public:
	vector<t_vertex> vert;
	vector<unsigned int> tri;

	t_material material;

	int curent_shader;

	glm::vec3 spawnPosition;
	glm::vec3 curentPosition;

	unsigned int VAO, VBO, EBO;
	void load_obj(std::string path);
	void setup_mesh();
	void draw(Shader shader);
};