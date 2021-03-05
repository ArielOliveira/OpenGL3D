#include "State.hpp"
#include "Material.hpp"

bool State::hasInitialized = false;

unsigned char State::whiteMap[] = { 255, 255, 255, 255};
unsigned char State::opaqueMap[] = { 64, 64, 64, 255};
unsigned char State::transparentMap[] = { 0, 0, 0, 0};
unsigned char State::blackMap[] = { 0, 0, 0, 255};

int State::dLightsCount = 0;
int State::pLightsCount = 0;
int State::sLightsCount = 0;

GLSLShader* State::defaultShader = nullptr;
Material* State::defaultMaterial = nullptr;
Material* State::defaultLightMaterial = nullptr;
Material* State::transparentMaterial = nullptr;
Material* State::blackMaterial = nullptr;

glm::mat4 State::projectionMatrix = glm::mat4(1);
glm::mat4 State::viewMatrix = glm::mat4(1);
glm::mat4 State::modelMatrix = glm::mat4(1);

bool State::initialize(GLSLShader* _defaultShader, Material* _defaultMaterial) {
	if (hasInitialized == true) {
		std::cerr << "Attempting to initialize State twice. Aborting." << std::endl;
		return false;
	}

	hasInitialized = true;

	if (_defaultShader && !defaultShader) {
		defaultShader = _defaultShader;
	} else {
		std::cerr << "Invalid shader assigning" << std::endl;
		return false;
	}

	if (_defaultMaterial && !defaultMaterial) {
		defaultMaterial = _defaultMaterial;
	} else {
		std::cerr << "Invalid texture assigning" << std::endl;
		return false;
	}

	if (!defaultLightMaterial) {
		defaultLightMaterial = new Material(new GLTexture(whiteMap, glm::vec2(1), 1),
										    new GLTexture(whiteMap, glm::vec2(1), 1),
										    new GLTexture(whiteMap, glm::vec2(1), 1),
										    32.f);
	} else {
		std::cerr << "Invalid material assigning" << std::endl;
		return false;
	}

	if (!transparentMaterial) {
		transparentMaterial = new Material(new GLTexture(transparentMap, glm::vec2(1), 1),
										   new GLTexture(transparentMap, glm::vec2(1), 1),
										   new GLTexture(transparentMap, glm::vec2(1), 1),
										   32.f);
	} else {
		std::cerr << "Invalid material assigning" << std::endl;
		return false;
	}

	if (!blackMaterial) {
		blackMaterial = new Material(new GLTexture(blackMap, glm::vec2(1), 1),
									 new GLTexture(blackMap, glm::vec2(1), 1),
									 new GLTexture(blackMap, glm::vec2(1), 1),
										   32.f);
	} else {
		std::cerr << "Invalid material assigning" << std::endl;
		return false;
	}

	return true;
}
