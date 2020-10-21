#include "model.h"

vector<glm::vec3> t_3d_model::do_collis(glm::vec3 curentPosition) { //нужно что-то по-оригинальнeе придумать, мб просто читать вершины, но тогда усложнитс€ расчет, и оптимизаци€ по ху€м пойдет
	
	vector <glm::vec3> collision_model;

	collision_model.push_back(glm::vec3(curentPosition.x - 0.5, curentPosition.y - 0.5, curentPosition.z - 0.5));
	collision_model.push_back(glm::vec3(curentPosition.x + 0.5, curentPosition.y - 0.5, curentPosition.z - 0.5));
	collision_model.push_back(glm::vec3(curentPosition.x + 0.5, curentPosition.y + 0.5, curentPosition.z - 0.5));
	collision_model.push_back(glm::vec3(curentPosition.x - 0.5, curentPosition.y + 0.5, curentPosition.z - 0.5));
	collision_model.push_back(glm::vec3(curentPosition.x - 0.5, curentPosition.y - 0.5, curentPosition.z + 0.5));
	collision_model.push_back(glm::vec3(curentPosition.x + 0.5, curentPosition.y - 0.5, curentPosition.z + 0.5));
	collision_model.push_back(glm::vec3(curentPosition.x + 0.5, curentPosition.y + 0.5, curentPosition.z + 0.5));
	collision_model.push_back(glm::vec3(curentPosition.x - 0.5, curentPosition.y + 0.5, curentPosition.z + 0.5));

	return collision_model;
}

void t_3d_model::load_obj(std::string path)
{
	fstream file_obj; 

	file_obj.open(path);
	if (file_obj.is_open()) 
	{
		string line;
		bool vn = false, vt = false;

		vector<glm::vec3> points;
		vector<glm::vec3> normals;
		vector<glm::vec2> textures;

		while (!file_obj.eof()) 
		{
			getline(file_obj, line);

			if (line[0] == 'v' && line[1] == ' ')
			{
				float x, y, z;
				sscanf_s(line.c_str(), "%*s %f %f %f",	//может быть ты мой crash из за этого
					&x,
					&y,
					&z
				);

				points.push_back({ x,y,z });
			}
			else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
			{
				float x, y, z;
				sscanf_s(line.c_str(), "%*s %f %f %f",	//может быть ты мой crash из за этого
					&x,
					&y,
					&z
				);
				normals.push_back({ x,y,z });
			}
			else if (line[0] == 'v' && line[1] == 't' && line[2] == ' ')
			{
				float x, y;
				sscanf_s(line.c_str(), "%*s %f %f",	//может быть ты мой crash из за этого
					&x,
					&y
				);

				textures.push_back({ x,y });
			}
			else if (line[0] == 'f' && line[1] == ' ')
			{
				int v[3];
				int n[3];
				int t[3];

				sscanf_s(line.c_str(), "%*s %i/%i/%i %i/%i/%i %i/%i/%i",
					&v[0], &t[0], &n[0],
					&v[1], &t[1], &n[1],
					&v[2], &t[2], &n[2]);

				for (int i = 0; i < 3; i++) {

					t_vertex key = {
						points[v[i] - 1],
						normals[n[i] - 1],
						textures[t[i] - 1]
					};

					vert.push_back(key);
					tri.push_back(vert.size()-1);

				}

			}
		}

	} else {
		cout << "ERROR: can't open file with path " << path << endl;
	}
}

void t_3d_model::setup_mesh()
{

	//calculateTan_biTan();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(t_vertex), &vert[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tri.size() * sizeof(unsigned int), &tri[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex), (void*)offsetof(t_vertex, norm));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(t_vertex), (void*)offsetof(t_vertex, text));

	/*glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex), (void*)offsetof(t_vertex, tan));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex), (void*)offsetof(t_vertex, biTan));*/

	glBindVertexArray(0);
}

void t_3d_model::draw_model(Shader& shader, t_3d_model& mod, Camera& camera, glm::mat4& view, glm::mat4& projection)
{
	//shader.Use();

	shader.setFloat("material.shininess", shininess);
	shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

	//mod.pointLight.load_to_shader(shader, 0);

	view = camera.GetViewMatrix();
	// Get the uniform locations
	GLint modelLoc = glGetUniformLocation(shader.Program, "model");
	GLint viewLoc = glGetUniformLocation(shader.Program, "view");
	GLint projLoc = glGetUniformLocation(shader.Program, "projection");
	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glm::mat4 model(1.0f);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.texture);
	glUniform1i(glGetUniformLocation(shader.Program, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture.blikMap);
	glUniform1i(glGetUniformLocation(shader.Program, "material.specular"), 1);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, tri.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void t_model::add_3d_model(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, string obj_path,float shininess, unsigned int curent_shader, const GLchar* strVs, const GLchar* strFrag, 
							t_shader& vShader, const char* texture_path , const char* blikMap_path, const char* normals_path)
{
	t_3d_model model;
	model.blik_map = false; model.normals_map = false; model.texture_map = false;
	model.ID = model_3d.size();

	model.transform.position = position;
	model.transform.rotation = rotation;
	model.transform.scale = scale;
	model.shininess = shininess;

	if (curent_shader != -1) {
		model.curent_shader = curent_shader;
		vShader.vec[curent_shader].depend_model.push_back(model.ID);
	}
	else {
		bool findShader = false;
		for (int i = 0; i < vShader.vec.size(); i++) {
			if (vShader.vec[i].strVs == strVs && vShader.vec[i].strFrag == strFrag)
			{
				findShader = true;
				model.curent_shader = i;
				vShader.vec[i].depend_model.push_back(model.ID);
			}
		}
		if (!findShader)
		{
			int success = vShader.load_shader(strVs, strFrag);
			if (success != -1)
			{
				model.curent_shader = vShader.vec.size()-1;
				vShader.vec[vShader.vec.size()-1].depend_model.push_back(model.ID);
			}
		}
	}

	if (obj_path != "") {
		model.load_obj(obj_path);
		model.setup_mesh();
	}

	if (texture_path != nullptr) {
		model.texture_map = true;
		model.texture.load_texture(texture_path);
	}
	if (blikMap_path != nullptr) {
		model.blik_map = true;
		model.texture.load_blikMap(blikMap_path);
	}
	if (normals_path != nullptr) {
		model.normals_map = true;
		model.texture.load_normals(normals_path);
	}

	model_3d.push_back(model);
}

void t_3d_model::calculateTan_biTan() {
	for (int i = 0; i < tri.size(); i+=3) {
		// calculate tangent/bitangent vectors of both triangles
		
		glm::vec3 edge1 = vert[tri[i + 1]].pos - vert[tri[i]].pos;
		glm::vec3 edge2 = vert[tri[i + 2]].pos - vert[tri[i]].pos;
		glm::vec2 deltaUV1 = vert[tri[i + 1]].text - vert[tri[i]].text;
		glm::vec2 deltaUV2 = vert[tri[i + 2]].text - vert[tri[i]].text;

		float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		vert[tri[i]].tan.x = vert[tri[i + 1]].tan.x = vert[tri[i + 2]].tan.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		vert[tri[i]].tan.y = vert[tri[i + 1]].tan.y = vert[tri[i + 2]].tan.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		vert[tri[i]].tan.z = vert[tri[i + 1]].tan.z = vert[tri[i + 2]].tan.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		//vert[tri[i]].tan = glm::normalize(vert[tri[i]].tan);


		vert[tri[i]].biTan.x = vert[tri[i + 1]].biTan.x = vert[tri[i + 2]].biTan.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		vert[tri[i]].biTan.y = vert[tri[i + 1]].biTan.y = vert[tri[i + 2]].biTan.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		vert[tri[i]].biTan.z = vert[tri[i + 1]].biTan.z = vert[tri[i + 2]].biTan.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		//vert[tri[i]].biTan = glm::normalize(vert[tri[i]].biTan);
	}
}