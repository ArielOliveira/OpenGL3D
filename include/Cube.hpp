#pragma once
#include "Object.hpp"
class Cube : public Object {
	private:
		Mesh* makeCube();
	public:
		Cube();
		Cube(const Cube& cube);
		Cube(const char* filename);
		Cube(const Material& material);
		~Cube();
		void step(float deltaTime);
};

