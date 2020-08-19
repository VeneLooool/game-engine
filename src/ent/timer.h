#include "../include.h"

struct timer{

	GLfloat delta_sec;
	GLfloat sec;
	GLfloat last_sec;
	GLfloat curr_sec;

	void calc_time();
};