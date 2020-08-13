#include "shader.h"
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

	int curent_shader;

	unsigned int VAO, VBO, EBO;
	void load_obj(std::string path);
	void setup_mesh();
	void draw(Shader shader);
};