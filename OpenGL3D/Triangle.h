#pragma once
#include "Model.h"

class Triangle : public Model {
	public:
		Triangle();
		Triangle(const Triangle& triangle);
		~Triangle();
		void step(float deltaTime);
};

