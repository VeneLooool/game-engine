#include "scene.h"

void t_scene::draw_scene(Camera& camera, int WIDTH, int HEIGHT)
{
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

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

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
			
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Model.model_3d[Shaders.vec[curShader].depend_model[curModel]].texture.texture);
			glUniform1i(glGetUniformLocation(Shaders.vec[curShader].Program, "material.diffuse"), 0);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, Model.model_3d[Shaders.vec[curShader].depend_model[curModel]].texture.blikMap);
			glUniform1i(glGetUniformLocation(Shaders.vec[curShader].Program, "material.specular"), 1);
			
			glBindVertexArray(Model.model_3d[Shaders.vec[curShader].depend_model[curModel]].VAO);
			glDrawElements(GL_TRIANGLES, Model.model_3d[Shaders.vec[curShader].depend_model[curModel]].tri.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

	}
}