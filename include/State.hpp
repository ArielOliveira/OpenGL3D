#pragma once
#include "GLSLShader.hpp"

class State {
public:
	static GLSLShader* defaultShader;
	static glm::mat4 projectionMatrix;
	static glm::mat4 viewMatrix;
	static glm::mat4 modelMatrix;
};

