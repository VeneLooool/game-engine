#include "../../include.h"
#include "colision_data.h"

class aabb {

public:

	aabb(const glm::vec3 first_e, const glm::vec3 second_e) :
		model_first_e(first_e), model_second_e(second_e) {}

	inline const glm::vec3 get_first_e() const{

		return model_first_e;

	}

	inline const glm::vec3 get_second_e() const{

		return model_second_e;

	}

	colision_data colision_aabb(const aabb &m_model) const;

private:

	const glm::vec3 model_first_e, model_second_e;

};