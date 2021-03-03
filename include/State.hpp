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
		static unsigned char whiteMap[];
		static unsigned char blackMap[];

		static int dLightsCount;
		static int pLightsCount;
		static int sLightsCount;
		
		static const unsigned char lightTypes[];

		static GLSLShader* defaultShader;
		static GLTexture* defaultTexture;
		static GLTexture* blackTexture;

		static glm::mat4 projectionMatrix;
		static glm::mat4 viewMatrix;
		static glm::mat4 modelMatrix;

		static bool initialize(GLSLShader* _defaultShader, GLTexture* _defaultTexture);
};

