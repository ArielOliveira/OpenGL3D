#pragma once
#include "Object3D.h"

class Triangle : public Object3D {
	public:
		Triangle();
		Triangle(const Triangle& triangle);
		~Triangle();
		void step(float deltaTime);
};

