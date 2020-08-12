#include "shader.h"

void t_shader::push_shader(Shader link) {
	vec.push_back(link);
}

void t_shader::load_shader(const GLchar* strVs, const GLchar* strFrag) {
	Shader ourShader(strVs, strFrag);

	push_shader(ourShader);
}