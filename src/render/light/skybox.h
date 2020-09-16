#include "../../include.h"
#include "../shader.h"

struct t_skybox
{
public:
	vector<Shader> shader;

	float skyboxVertices;

	unsigned int skyboxVAO, skyboxVBO;
	unsigned int cubemapTexture;
	
	void addSkybox(const GLchar* pathVs, const GLchar* pathFrag, string pathRight, string pathLeft, string pathTop, string pathBottom, string pathFront, string pathBack);
	void drawSkybox(glm::mat4 view, glm::mat4 projection);
};