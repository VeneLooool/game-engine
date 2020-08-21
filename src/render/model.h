#include "shader.h"
#include "material.h"
#include "texture.h"
#include "../include.h"
#include "camera.h"
#include "../core/physic/transform.h"



struct  t_vertex
{
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 text;
};

struct phys_properties{

	double wieght;
	double v0_fall, t0_fall, v_fall, t_fall, h_fall;

};

struct t_3d_model
{
public:
	unsigned int ID;
	t_transform transform;

	vector<t_vertex> vert;
	vector<unsigned int> tri;

	t_material material;

	t_texture texture;

	int curent_shader;
	float shininess;

	phys_properties physical_properties;
	vector<glm::vec3> collision_model;

	//glm::vec3 spawnPosition; //убрать 
	//glm::vec3 curentPosition; //убрать 
	glm::vec3 vector_moving; //убрать 

	unsigned int VAO, VBO, EBO;

	void setup_mesh();
	void load_obj(std::string path);

	vector <glm::vec3> do_collis(glm::vec3 curentPosition);
	void draw_model(Shader& shader, t_3d_model& mod, Camera& camera, glm::mat4& view, glm::mat4& projection);
};

struct t_model {
public:
	vector<t_3d_model> model_3d;

	void add_3d_model(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, string obj_path, float shininess, unsigned int curent_shader, const GLchar* strVs, const GLchar* strFrag, 
						t_shader& vShader, const char* texture_path, const char* blikMap_path);
};