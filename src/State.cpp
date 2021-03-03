#include "State.hpp"

bool State::hasInitialized = false;

unsigned char State::whiteMap[] = { 255, 255, 255};
unsigned char State::blackMap[] = { 0, 0, 0};

int State::dLightsCount = 0;
int State::pLightsCount = 0;
int State::sLightsCount = 0;

GLSLShader* State::defaultShader = nullptr;
GLTexture* State::defaultTexture = nullptr;
GLTexture* State::blackTexture = nullptr;

glm::mat4 State::projectionMatrix = glm::mat4(1);
glm::mat4 State::viewMatrix = glm::mat4(1);
glm::mat4 State::modelMatrix = glm::mat4(1);

bool State::initialize(GLSLShader* _defaultShader, GLTexture* _defaultTexture) {
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

	if (_defaultTexture && !defaultTexture) {
		defaultTexture = _defaultTexture;
	} else {
		std::cerr << "Invalid texture assigning" << std::endl;
		return false;
	}

	if (!blackTexture) {
		blackTexture = new GLTexture(blackMap, glm::vec2(1), 1);
	} else {
		std::cerr << "Invalid texture assigning" << std::endl;
		return false;
	}

	return true;
}
