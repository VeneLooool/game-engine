#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "../include.h"
#include "../render/shader.h"


void init_GL();
GLFWwindow* create_window(GLuint WIDTH, GLuint HEIGHT, const char* str);
void setup_bufers(GLuint VAO, GLuint EBO, GLuint VBO);
void delete_buffers(GLuint VAO, GLuint EBO, GLuint VBO);