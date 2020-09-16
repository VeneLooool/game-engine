#include "aabb.h"

colision_data aabb::colision_aabb(const aabb &m_model) const {

	glm::vec3 d1 = m_model.get_first_e() - m_model.get_second_e();
	glm::vec3 d2 = model_first_e - m_model.get_second_e();
	
	glm::vec3 dist;
	for (int i = 0; i < d1.length(); i++) {
		dist[i] = d1[i] > d2[i] ? d1[i] : d2[i];
	}

	float maxd = dist[0];
	for (int i = 1; i < dist.length(); i++) {
		if (dist[i] > maxd)
			maxd = dist[i];
	}

	return colision_data(maxd < 0, maxd);
}