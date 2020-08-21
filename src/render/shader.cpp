#include "shader.h"

void t_shader::push_shader(Shader link) {
	vec.push_back(link);
}

int t_shader::load_shader(const GLchar* strVs, const GLchar* strFrag) {
	int success = 0;
	Shader ourShader(strVs, strFrag, success);

	ourShader.idV = vec.size();
	ourShader.strVs = strVs;
	ourShader.strFrag = strFrag;
	
	if(success!=-1)
		push_shader(ourShader);
	return(success);
}