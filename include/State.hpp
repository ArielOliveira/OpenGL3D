#pragma once
#include "GLSLShader.hpp"
#include "Mesh.hpp"

#include <string>
using std::string;

#include <map>
using std::map;

class Material;

class State {
	private:
		static bool hasInitialized;
	public:
		static unsigned char whiteMap[];
		static unsigned char opaqueMap[];
		static unsigned char transparentMap[];
		static unsigned char blackMap[];

		static int dLightsCount;
		static int pLightsCount;
		static int sLightsCount;

		static GLSLShader* defaultShader;
		
		static Material* defaultMaterial;
		static Material* defaultLightMaterial;
		static Material* transparentMaterial;
		static Material* blackMaterial;

		static glm::mat4 projectionMatrix;
		static glm::mat4 viewMatrix;
		static glm::mat4 modelMatrix;

		static bool initialize(GLSLShader* _defaultShader, Material* _defaultMaterial);
};

