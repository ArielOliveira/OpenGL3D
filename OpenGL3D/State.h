#pragma once
#include "GLSLShader.h"
#include <GLFW/glfw3.h>

class State {
public:
	static GLSLShader* defaultShader;
	static glm::mat4 projectionMatrix;
	static glm::mat4 viewMatrix;
	static glm::mat4 modelMatrix;

	static char keybEvent[512];

	static double lastMouseX;
	static double lastMouseY;

	static double xRoll; //yaw
	static double yRoll; //pitch

	static double mouseSensitivity;

	static double deltaTime;
	
	static bool firstInput;

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int
		mods);

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
};

