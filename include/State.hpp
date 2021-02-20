#pragma once
#include "GLSLShader.hpp"
#include "Mesh.hpp"
#include "GLTexture.hpp"

#include <string>
using std::string;

#include <map>
using std::map;

class State {
	private:
		static bool hasInitialized;
	public:
		static const unsigned char whiteMap[];
		static const unsigned char blackMap[];

		static GLSLShader* defaultShader;
		static GLTexture* defaultTexture;
		static GLTexture* blackTexture;

		static glm::mat4 projectionMatrix;
		static glm::mat4 viewMatrix;
		static glm::mat4 modelMatrix;

		static map<string, Mesh*>* meshHash;
		static map<string, GLTexture*>* textureHash;
		static map<string, GLSLShader*>* shaderHash;

		static bool initialize(GLSLShader* _defaultShader, GLTexture* _defaultTexture);

		static glm::vec3 QuaternionToVector(glm::quat quat, glm::vec3 vec);

		static glm::quat getRotation(glm::vec3 dir, float angle);
};

