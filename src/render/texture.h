#include "../include.h"

struct t_texture
{
public:
	GLuint texture;
	GLuint blikMap;

	void load_texture(const char* path);
	void load_blikMap(const char* path);
};