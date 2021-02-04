#pragma once
#include "Object3D.h"
#include "State.h"
class Cube : public Object3D {
public:
	Cube();
	Cube(const Cube& cube);
	Cube(const char* filename);
	~Cube();
	void step(float deltaTime);
};

