#pragma once
#include "GLSLShader.h"

class State {
public:
	static GLSLShader* defaultShader;
	static glm::mat4 projectionMatrix;
	static glm::mat4 viewMatrix;
	static glm::mat4 modelMatrix;
};

