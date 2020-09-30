#include "../include.h"

class timer{
public:

	GLfloat delta_sec;
	GLfloat sec;
	GLfloat last_sec;
	GLfloat curr_sec;

	void calc_time();
};