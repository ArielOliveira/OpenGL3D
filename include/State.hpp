#pragma once
#include "GLSLShader.hpp"

class State {
public:
	static GLSLShader* defaultShader;
	static glm::mat4 projectionMatrix;
	static glm::mat4 viewMatrix;
	static glm::mat4 modelMatrix;

	static glm::vec3 QuaternionToVector(glm::quat quat, glm::vec3 vec);

	static glm::quat getRotation(glm::vec3 dir, float angle);
};

