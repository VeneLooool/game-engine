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
			
			vertex vert_scan;
			triangle tri_scan;

			if (line[0] == 'v' && line[1] == ' ')
			{
				sscanf_s(line.c_str(), "%*s %f %f %f",	//может быть crash из за этого
					&vert_scan.v.pos.x,
					&vert_scan.v.pos.y,
					&vert_scan.v.pos.z
				);

				vert.push_back(vert_scan);
			}
			else if (line[0] == 'f' && line[1] == ' ')
			{		
				sscanf_s(line.c_str(), "%*s %i %i %i", //может быть crash из за этого
					&tri_scan.index[0],
					&tri_scan.index[1],
					&tri_scan.index[2]
				);

				tri.push_back(tri_scan);
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
