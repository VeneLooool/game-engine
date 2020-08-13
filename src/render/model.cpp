#include "model.h"

//TODO: �������� �������� �������� ����� ���� �� ������ �������, � �������, �������� 

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
				sscanf_s(line.c_str(), "%*s %f %f %f",	//����� ���� crash �� �� �����
					&x,
					&y,
					&z
				);

				points.push_back({ x,y,z });
			}
			else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
			{
				float x, y, z;
				sscanf_s(line.c_str(), "%*s %f %f %f",	//����� ���� crash �� �� �����
					&x,
					&y,
					&z
				);
				normals.push_back({ x,y,z });
			}
			else if (line[0] == 'v' && line[1] == 't' && line[2] == ' ')
			{
				float x, y;
				sscanf_s(line.c_str(), "%*s %f %f",	//����� ���� crash �� �� �����
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

void t_model::draw(Shader shader)
{
	shader.Use();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, tri.size()*3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
