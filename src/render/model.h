#include "shader.h"
#include "material.h"
#include "texture.h"
#include "../include.h"
#include "camera.h"
#include "../core/physic/transform.h"



class  t_vertex
{
public:
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 text;
	glm::vec3 tan;
	glm::vec3 biTan;
};

class phys_properties{
public:
	double wieght;
	double v0_fall, t0_fall, v_fall, t_fall, h_fall;

};

class t_3d_model
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

	bool texture_map, normals_map, blik_map;

	phys_properties physical_properties;
	vector<glm::vec3> collision_model;

	unsigned int VAO, VBO, EBO;

	void setup_mesh();
	void load_obj(std::string path);

	vector <glm::vec3> do_collis(glm::vec3 curentPosition);
	void draw_model(Shader& shader, t_3d_model& mod, Camera& camera, glm::mat4& view, glm::mat4& projection);

	void calculateTan_biTan();
};

class t_model {
public:
	vector<t_3d_model> model_3d;

	void add_3d_model(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, string obj_path, float shininess, unsigned int curent_shader, const GLchar* strVs, const GLchar* strFrag, 
						t_shader& vShader, const char* texture_path = nullptr, const char* blikMap_path = nullptr, const char* normals_path = nullptr);
};