#include "Triangle.h"
#include "GLRender.h"

Triangle::Triangle() {}

Triangle::Triangle(const Triangle& triangle) : Model(triangle) {}

Triangle::~Triangle() {}

void Triangle::step(float deltaTime) {
	rot.y = fmodf(rot.y + glm::radians(32.0f) * deltaTime, glm::radians(360.0f));
	Model::step(deltaTime);
}
