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

	int wieght;
	vector<glm::vec3> collision_model;

	glm::vec3 spawnPosition;
	glm::vec3 curentPosition;
	glm::vec3 vector_moving;

	unsigned int VAO, VBO, EBO;
	void load_obj(std::string path);
	void do_collis(vector<glm::vec3> collision_model);
	void setup_mesh();
	void draw(Shader shader);
};