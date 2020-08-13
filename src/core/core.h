//#include "../gl/gl.h	"
#include "../render/model.h"
#include "../render/camera.h"

void main_loop(); 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
