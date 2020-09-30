#include "../core/core.h"
#include "gl.h"



void init_GL() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

GLFWwindow* create_window(GLuint WIDTH, GLuint HEIGHT, const char* str)
{
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, str, nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;

	glewInit();

	glViewport(0, 0, WIDTH, HEIGHT);
	
	glEnable(GL_DEPTH_TEST);

	return(window);	
}	
