#include "model.h"

//TODO: доделать загрузку объектов когда есть не только вершины, а нормали, текстуры 

vector<glm::vec3> t_model::do_collis(glm::vec3 curentPosition) { //нужно что-то по-оригинальнeе придумать, мб просто читать вершины, но тогда усложнитс€ расчет, и оптимизаци€ по ху€м пойдет
	
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

void t_model::load_obj(std::string path)
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

void t_model::setup_mesh() 
{
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

	glBindVertexArray(0);
}

void t_model::draw_model(Shader& shader, t_model& mod, Camera& camera, glm::mat4& view, glm::mat4& projection)
{
	//shader.Use();

	shader.setFloat("material.shininess", shininess);
	shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

	mod.pointLight.load_to_shader(shader, 0);

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

