#include "scene.h"

void t_scene::draw_scene(Camera& camera, int WIDTH, int HEIGHT, unsigned int depthMapFBO, unsigned int depthMap, unsigned int hdrFBO, Shader& shader_depth, Shader& shaderBlur, Shader& shaderBloomFinal)
{
	glm::vec3 lightPos(-0.8f, 0.8f, -0.8f);

	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

	const unsigned int SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;

	float near_plane = 1.0f;
	float far_plane = 25.0f;
	
	//включить для обработки teni
	/*
	glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
	std::vector<glm::mat4> shadowTransforms;
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

	
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	shader_depth.Use();

	for (unsigned int i = 0; i < 6; ++i)
		shader_depth.setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
	shader_depth.setFloat("far_plane", far_plane);
	shader_depth.setVec3("lightPos", lightPos);

	shadow_render(shader_depth);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, WIDTH, HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	*/
	bool shadows = false;

	//prikol v framebufferax

	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO); //проблема с тенями в буферах различных 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int curShader = 0; curShader < Shaders.vec.size(); curShader++)
	{
		Shaders.vec[curShader].Use();
		Shaders.vec[curShader].setVec3("viewPos", camera.Position);
		
		for (unsigned int i = 0; i < Light.pointLight.size(); i++)
		{
			Shaders.vec[0].setVec3("lights[" + std::to_string(i) + "].Position", Light.pointLight[i].transform.position);
			Shaders.vec[0].setVec3("lights[" + std::to_string(i) + "].Color", Light.pointLight[i].color);
		}
	
		Shaders.vec[curShader].setMat4("projection", projection);
		Shaders.vec[curShader].setMat4("view", view);

		Shaders.vec[curShader].setVec3("lightPos", lightPos);
		
		Shaders.vec[curShader].setInt("shadows", shadows); // enable/disable shadows by pressing 'SPACE'
		Shaders.vec[curShader].setFloat("far_plane", far_plane);



		for (int curModel = 0; curModel < Shaders.vec[curShader].depend_model.size(); curModel++)
		{
			
			glm::mat4 model(1.0f);
			model = glm::translate(model, Model.model_3d[Shaders.vec[curShader].depend_model[curModel]].transform.position);
			model = glm::scale(model, Model.model_3d[Shaders.vec[curShader].depend_model[curModel]].transform.scale);
			//added rotate
			
			Shaders.vec[curShader].setMat4("model", model);
			Shaders.vec[1].setVec3("lightColor", Light.pointLight[0].color); //!!!

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Model.model_3d[Shaders.vec[curShader].depend_model[curModel]].texture.texture);

			//glActiveTexture(GL_TEXTURE1);
			//glBindTexture(GL_TEXTURE_CUBE_MAP, depthMap);

			glBindVertexArray(Model.model_3d[Shaders.vec[curShader].depend_model[curModel]].VAO);
			glDrawElements(GL_TRIANGLES, Model.model_3d[Shaders.vec[curShader].depend_model[curModel]].tri.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

	}

	SkyBox.drawSkybox(view, projection);
}

void t_scene::shadow_render(const Shader& shader) {
	
	//glEnable(GL_CULL_FACE);
	
	// floor
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, Model.model_3d[0].transform.position);
	model = glm::scale(model, Model.model_3d[0].transform.scale);
	shader.setMat4("model", model);
	// render Cube
	glBindVertexArray(Model.model_3d[0].VAO);
	glDrawElements(GL_TRIANGLES, Model.model_3d[0].tri.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// cubes
	model = glm::mat4(1.0f);
	model = glm::translate(model, Model.model_3d[1].transform.position);
	model = glm::scale(model, Model.model_3d[1].transform.scale);
	shader.setMat4("model", model);
	// render Cube
	glBindVertexArray(Model.model_3d[1].VAO);
	glDrawElements(GL_TRIANGLES, Model.model_3d[1].tri.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	model = glm::mat4(1.0f);
	model = glm::translate(model, Model.model_3d[2].transform.position);
	model = glm::scale(model, Model.model_3d[2].transform.scale);
	shader.setMat4("model", model);
	// render Cube
	glBindVertexArray(Model.model_3d[2].VAO);
	glDrawElements(GL_TRIANGLES, Model.model_3d[2].tri.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}