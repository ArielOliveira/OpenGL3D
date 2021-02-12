#pragma once
#include "Model.hpp"
#include "State.hpp"
class Cube : public Model {
public:
	Cube();
	Cube(const Cube& cube);
	Cube(const char* filename);
	~Cube();
	void step(float deltaTime);
};

