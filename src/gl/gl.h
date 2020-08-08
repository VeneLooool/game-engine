#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "../include.h"
#include "shader/shader.h"


void init_GL();
GLFWwindow* create_window(GLuint WIDTH, GLuint HEIGHT, const char* str);
Shader& setup_shaders(GLchar strVs, GLchar strFrag);
void setup_bufers(GLuint VAO, GLuint EBO, GLuint VBO);
void delete_shader(GLuint VAO, GLuint EBO, GLuint VBO);