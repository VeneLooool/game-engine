#include "shader.h"
#include "material.h"
#include "texture.h"
#include "light/light.h"
#include "../include.h"
#include "camera.h"


struct  t_vertex
{
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 text;
};

struct t_model
{

public:
	vector<t_vertex> vert;
	vector<unsigned int> tri;

	t_material material;

	t_texture texture;

	t_dirLight dirLight;
	t_pointLight pointLight;
	t_spotLight spotLight;

	int curent_shader;
	float shininess;

	int wieght;
	vector<glm::vec3> collision_model;

	glm::vec3 spawnPosition;
	glm::vec3 curentPosition;
	glm::vec3 vector_moving;

	unsigned int VAO, VBO, EBO;
	void load_obj(std::string path);
	void do_collis(vector<glm::vec3> collision_model);
	void setup_mesh();
	void draw_model(Shader& shader, t_model& mod, Camera& camera, glm::mat4& view, glm::mat4& projection);
};