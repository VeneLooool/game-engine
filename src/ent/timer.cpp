#include "timer.h"

void timer::calc_time() {

	curr_sec = glfwGetTime();
	delta_sec = curr_sec - last_sec;
	last_sec = curr_sec;

}