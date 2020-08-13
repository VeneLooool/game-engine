#include "model.h"

//TODO: доделать загрузку объектов когда есть не только вершины, а нормали, текстуры 

void t_model::load_obj(std::string path)
{
	fstream file_obj; 

	file_obj.open(path);
	if (file_obj.is_open()) 
	{
		string line;
		bool vn = false, vt = false;

		while (!file_obj.eof()) 
		{
			getline(file_obj, line);
			
			t_vertex vert_scan;
			unsigned int tri_scan[3];

			if (line[0] == 'v' && line[1] == ' ')
			{
				sscanf_s(line.c_str(), "%*s %f %f %f",	//может быть crash из за этого
					&vert_scan.pos.x,
					&vert_scan.pos.y,
					&vert_scan.pos.z
				);

				vert.push_back(vert_scan);
			}
			else if (line[0] == 'f' && line[1] == ' ')
			{		
				sscanf_s(line.c_str(), "%*s %i %i %i", //может быть crash из за этого
					&tri_scan[0],
					&tri_scan[1],
					&tri_scan[2]
				);

				tri.push_back(tri_scan[0]-1); tri.push_back(tri_scan[1]-1); tri.push_back(tri_scan[2]-1);
			}
			else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
			{


			}
			else if (line[0] == 'v' && line[1] == 't' && line[2] == ' ')
			{


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
