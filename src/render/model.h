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

/*struct t_texture 
{
	//unsigned int id;
	//string type;
public:
	GLuint texture;
	GLuint blikMap;

	void load_texture(const char* path);
	void load_blikMap(const char* path);
};*/

struct phys_properties{

	double wieght;
	double v0_fall, t0_fall, v_fall, t_fall, h_fall;

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

	phys_properties physical_properties;
	vector<glm::vec3> collision_model;

	glm::vec3 spawnPosition;
	glm::vec3 curentPosition;
	glm::vec3 vector_moving;

	unsigned int VAO, VBO, EBO;
	void load_obj(std::string path);
	vector <glm::vec3> do_collis(glm::vec3 curentPosition);
	void setup_mesh();
	void draw_model(Shader& shader, t_model& mod, Camera& camera, glm::mat4& view, glm::mat4& projection);
};