#include "timer.h"

void calc_time(timer time) {

	GLfloat current_frame;

	current_frame = glfwGetTime();
	time.delta_sec = current_frame - time.last_sec;
	time.last_sec = current_frame;
}