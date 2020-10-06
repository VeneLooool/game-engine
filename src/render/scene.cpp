#include "scene.h"

void t_scene::draw_scene(Camera& camera, int WIDTH, int HEIGHT, unsigned int depthMap)
{
	glm::vec3 light_Pos(-2.0f, 2.0f, -1.0f);

	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	float near_plane = 1.0f, far_plane = 7.5f;
	//lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = glm::lookAt(light_Pos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;

	for (int curShader = 0; curShader < Shaders.vec.size(); curShader++)
	{
		Shaders.vec[curShader].Use();
		Shaders.vec[curShader].setVec3("viewPos", camera.Position);
		Shaders.vec[curShader].setFloat("material.shininess", 32.0f);

		for (int curPointLight = 0; curPointLight < Light.pointLight.size(); curPointLight++)
		{
			Light.pointLight[curPointLight].load_to_shader(Shaders.vec[curShader], curPointLight);
		}
		for (int curDirectlight = 0; curDirectlight < Light.dirLight.size(); curDirectlight++)
		{
			Light.dirLight[curDirectlight].load_to_shader(Shaders.vec[curShader], curDirectlight);
		}

		for (int curModel = 0; curModel < Shaders.vec[curShader].depend_model.size(); curModel++)
		{

			// Get the uniform locations
			GLint modelLoc = glGetUniformLocation(Shaders.vec[curShader].Program, "model");
			GLint viewLoc = glGetUniformLocation(Shaders.vec[curShader].Program, "view");
			GLint projLoc = glGetUniformLocation(Shaders.vec[curShader].Program, "projection");

			// Pass the matrices to the shader
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			
			glm::mat4 model(1.0f);
			model = glm::translate(model, Model.model_3d[Shaders.vec[curShader].depend_model[curModel]].transform.position);
			model = glm::scale(model, Model.model_3d[Shaders.vec[curShader].depend_model[curModel]].transform.scale);
			//added rotate
			
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			Shaders.vec[curShader].setVec3("lightPos", light_Pos);
			Shaders.vec[curShader].setMat4("lightSpaceMatrix", lightSpaceMatrix);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Model.model_3d[Shaders.vec[curShader].depend_model[curModel]].texture.texture);
			glUniform1i(glGetUniformLocation(Shaders.vec[curShader].Program, "material.diffuse"), 0);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, Model.model_3d[Shaders.vec[curShader].depend_model[curModel]].texture.blikMap);
			glUniform1i(glGetUniformLocation(Shaders.vec[curShader].Program, "material.specular"), 1);

			//передача карты глубины в шейдер	
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, depthMap);
			glUniform1i(glGetUniformLocation(Shaders.vec[curShader].Program, "shadowMap"), 2);

			glBindVertexArray(Model.model_3d[Shaders.vec[curShader].depend_model[curModel]].VAO);
			glDrawElements(GL_TRIANGLES, Model.model_3d[Shaders.vec[curShader].depend_model[curModel]].tri.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

	}
	SkyBox.drawSkybox(view, projection);
}

void t_scene::shadow_render(const Shader& shader) {
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