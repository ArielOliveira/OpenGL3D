#pragma once
#include "Model.h"
#include "State.h"
class Cube : public Model {
public:
	Cube();
	Cube(const Cube& cube);
	Cube(const char* filename);
	~Cube();
	void step(float deltaTime);
};

