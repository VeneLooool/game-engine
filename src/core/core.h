//#include "../gl/gl.h	"
#include "../render/camera.h"
//#include "physic/physics.h"
//#include "../ent/timer.h"
#include "../render/scene.h"
#include "../include_physic.h"

void main_loop(); 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
