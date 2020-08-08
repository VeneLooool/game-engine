#include "core.h"
#include "../include.h"

GLuint VAO, VBO, EBO;

void main_loop() 
{
    init_GL();

    GLFWwindow* window = create_window(800, 600, "Engine");

	Shader& ourShader = setup_shaders((GLchar)"shader/shader.vs", (GLchar)"shader/shader.frag");

	setup_bufers(VAO, EBO, VBO);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        //RENDER

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }
	delete_shader(VAO, EBO, VBO);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}