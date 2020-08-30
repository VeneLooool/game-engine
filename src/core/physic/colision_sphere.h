#include "../../include.h"
#include "colision_data.h"

class colision_sphere {

public:

	colision_sphere(const glm::vec3 center, float radius) :
		model_center(center), model_radius(radius) {}

	inline const glm::vec3 get_center() const {
	
		return model_center;
	
	}

	inline float get_radius() const {
		
		return model_radius;

	}

	colision_data bounding_colision_sphere(const colision_sphere &m_model);

private:

	const glm::vec3 model_center;
	const float model_radius;

};