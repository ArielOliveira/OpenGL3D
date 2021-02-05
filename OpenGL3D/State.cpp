#include "State.h"

GLSLShader* State::defaultShader = nullptr;
glm::mat4 State::projectionMatrix = glm::mat4(1);
glm::mat4 State::viewMatrix = glm::mat4(1);
glm::mat4 State::modelMatrix = glm::mat4(1);
char State::keybEvent[512];

// Input
float State::leftAxisX = 0;
float State::leftAxisY = 0;

double State::lastMouseX = 0;
double State::lastMouseY = 0;

double State::mouseX = 0;
double State::mouseY = 0;

double State::mouseSensitivity = .1f;

bool State::firstInput = true;
/// ///////////////////////////

void State::keyCallback(GLFWwindow* window, int key, int scancode, int action, int
	mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		keybEvent[key] = 1;
		setAxis(key, 1);
		break;
	case GLFW_RELEASE:
		keybEvent[key] = 0;
		setAxis(key, 0);
		break;
	default:
		break;
	}
}

void State::setAxis(int key, int input) {
	switch (key) {
		case GLFW_KEY_W: leftAxisY = input;
			break;
		case GLFW_KEY_S: leftAxisY = -input;
			break;
		case GLFW_KEY_A: leftAxisX = -input;
			break;
		case GLFW_KEY_D: leftAxisX = input;
			break;
	}
}

void State::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstInput) {
		lastMouseX = xpos;
		lastMouseY = ypos;
		firstInput = false;
	}
	mouseX += (xpos - lastMouseX) * mouseSensitivity;
	mouseY += (ypos - lastMouseY) * mouseSensitivity;

	lastMouseX = xpos;
	lastMouseY = ypos;

	mouseX = fmodf(mouseX, 360.0f);
	
	if (mouseY > 89.f)
		mouseY = 89.f;
	if (mouseY < -89.f)
		mouseY = -89.f;
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
