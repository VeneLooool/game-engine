#include "../include.h"
//#include "light/light.h"
#include "../core/physic/physics.h"
#include "light/skybox.h"

class t_scene
{
public:
	t_light Light;
	t_model Model;
	t_shader Shaders;
	t_skybox SkyBox;
	//Camera MainCamera;

	void draw_scene(Camera& camera, int WIDTH, int HEIGHT, unsigned int depthMap);
	void shadow_render(const Shader& shader);
};