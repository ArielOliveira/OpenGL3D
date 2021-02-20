#pragma once
#include "Model.hpp"
class Cube : public Model {
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

