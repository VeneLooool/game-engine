class colision_data {

public:

	colision_data(const bool does_colision, const float dist) :
		model_does_colision(does_colision), model_dist(dist) {}

	inline bool get_does_colision() const {
	
		return model_does_colision;
	
	}
	
	inline float get_dist() const {
		
		return model_dist;
	
	}

private:

	const bool model_does_colision;
	const float model_dist;

};