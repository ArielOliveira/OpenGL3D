#include "Input.hpp"

// Virtual Axis //////////////////////
float Input::leftAxisX = 0;
float Input::leftAxisY = 0;

float Input::rightAxisX = 0;
float Input::rightAxisY = 0;
//////////////////////////////////////

// Mouse Input //////////////////////
double Input::lastMouseX = 0;
double Input::lastMouseY = 0;

double Input::currentMouseX = 0;
double Input::currentMouseY = 0;

double Input::mouseX = 0;
double Input::mouseY = 0;

double Input::mouseSensitivity = .1f;

bool Input::firstInput = true;
//////////////////////////////////////

// Keyboard Mapping ///////////////////////
bool Input::keyEventMap[512] = { false };
//////////////////////////////////////////

/// Joystick input
bool Input::gamepad[4] = { false };
float Input::leftJoySensitivity = .8f;
float Input::rightJoySensitivity = .8f;
float Input::deadZone = .05f;
//////////////////////////////////////

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int
	mods) {
	switch (action) {
		case GLFW_PRESS:
			keyEventMap[key] = true;
			setAxis(key, action);
			break;
		case GLFW_RELEASE:
			keyEventMap[key] = false;
			setAxis(key, action);
			break;
		default:
			break;
	}
}

void Input::setAxis(int key, int action) {
	if (key == GLFW_KEY_W || key == GLFW_KEY_S || key == GLFW_KEY_A || key == GLFW_KEY_D) {
		leftAxisY = keyEventMap[GLFW_KEY_W] + -keyEventMap[GLFW_KEY_S];
		leftAxisX = -keyEventMap[GLFW_KEY_A] + keyEventMap[GLFW_KEY_D];
	}
}

void Input::setAxis(int joyid, float axisArray[4], GLFWgamepadstate state) {
	leftAxisX = (abs(state.axes[0]) > deadZone ? state.axes[0] : .0f) * leftJoySensitivity;
	leftAxisY = (abs(state.axes[1]) > deadZone ? -state.axes[1] : .0f) * leftJoySensitivity;
	rightAxisX = (abs(state.axes[2]) > deadZone ? state.axes[2] : .0f) * rightJoySensitivity;
	rightAxisY = (abs(state.axes[3]) > deadZone ? state.axes[3] : .0f) * rightJoySensitivity;
}

void Input::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstInput) {
		currentMouseX = xpos;
		currentMouseY = ypos;
		lastMouseX = xpos;
		lastMouseY = ypos;
		firstInput = false;
	}

	currentMouseX = xpos;
	currentMouseY = ypos;
}

void Input::joystick_callback(int jid, int event) {
	if (event == GLFW_CONNECTED) {
		gamepad[jid] = true;
	}
	else if (event == GLFW_DISCONNECTED) {
		gamepad[jid] = false;
	}
}

void Input::update() {
	GLFWgamepadstate state;

	if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state)) {
		float axisArray[] = { GLFW_GAMEPAD_AXIS_LEFT_X, GLFW_GAMEPAD_AXIS_LEFT_Y,
							 GLFW_GAMEPAD_AXIS_RIGHT_X, GLFW_GAMEPAD_AXIS_RIGHT_Y };
		setAxis(GLFW_JOYSTICK_1, axisArray, state);
	} 

	mouseX = (currentMouseX - lastMouseX) * mouseSensitivity;
	mouseY = (currentMouseY - lastMouseY) * mouseSensitivity;

	lastMouseX = currentMouseX;
	lastMouseY = currentMouseY;
}