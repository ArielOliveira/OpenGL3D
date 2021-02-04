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
	

	static bool firstInput;

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int
		mods)
	{
		switch (action)
		{
		case GLFW_PRESS:
			//printf("Tecla apretada %d\n", key);
			keybEvent[key] = 1;
			break;
		case GLFW_RELEASE:
			//printf("Tecla levantada %d\n", key);
			keybEvent[key] = 0;
			break;
		default:
			break;
		}
	}

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (firstInput) {
			lastMouseX = xpos;
			lastMouseY = ypos;
			firstInput = false;
		}
		float inputX = xpos - lastMouseX;
		float inputY = ypos - lastMouseY;

		lastMouseX = xpos;
		lastMouseY = ypos;

		xRoll += inputX;
		yRoll += inputY;
		
		if (yRoll > 89.f)
			yRoll = 89.f;
		if (yRoll < -89.f)
			yRoll = -89.f;
		//mouseInput.x = fmodf(mouseInput.x, )
	}

	static glm::vec3 QuaternionToVector(glm::quat quat, glm::vec3 vec) {
		float num = quat.x * 2.f;
		float num2 = quat.y * 2.f;
		float num3 = quat.z * 2.f;
		float num4 = quat.x * num;
		float num5 = quat.y * num2;
		float num6 = quat.z * num3;
		float num7 = quat.x * num2;
		float num8 = quat.x * num3;
		float num9 = quat.y * num3;
		float num10 = quat.w * num;
		float num11 = quat.w * num2;
		float num12 = quat.w * num3;
		glm::vec3 result(0);
		result.x = (1.f - (num5 + num6)) * vec.x + (num7 - num12) * vec.y + (num8 + num11) * vec.z;
		result.y = (num7 + num12) * vec.x + (1.f - (num4 + num6)) * vec.y + (num9 - num10) * vec.z;
		result.z = (num8 - num11) * vec.x + (num9 + num10) * vec.y + (1.f - (num4 + num5)) * vec.z;
		return result;
	}
};

