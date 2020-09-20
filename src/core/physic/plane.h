#include "../../include.h"

class plane{

public:

	plane(const glm::vec3 normali, const float dist) :
		normal(normali), distance(dist) {}

	plane normalize() const;

	inline const glm::vec3 get_normal() const {

		return normal;

	}

	inline const float get_distance() const {

		return distance;

	}

private:

	const glm::vec3 normal;
	const float distance;

};