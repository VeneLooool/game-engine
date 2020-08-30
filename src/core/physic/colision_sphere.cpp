#include "colision_sphere.h"

colision_data colision_sphere::bounding_colision_sphere(const colision_sphere& m_model) {

	float rd = model_radius + m_model.get_radius;                 //radius
	float cd = (m_model.get_center() - model_center).length();    //center

	colision_data(cd < rd, cd - rd);

}