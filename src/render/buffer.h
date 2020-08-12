#include "../gl/gl.h"

class t_buffer 
{

public:
	vector<GLuint> VAO;
	vector<GLuint> VBO;
	//vector<GLuint> EBO;

	void setup_frame_buffer(size_t s_VAO, size_t s_VBO);
};