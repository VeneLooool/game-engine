#include "../include.h"

class t_texture
{
public:
	GLuint texture;
	GLuint blikMap;
	GLuint normals;

	void load_texture(const char* path);
	void load_blikMap(const char* path);
	void load_normals(const char* path);
};