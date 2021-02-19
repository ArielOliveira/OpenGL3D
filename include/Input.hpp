#pragma once
#include <iostream>
#include <glfw3.h>

class Input {
private:
	static void setAxis();
	static void setAxis(int joyid, float axisArray[4], GLFWgamepadstate);
public:
	/// Virtual Axis ////////////////////////////
	static float leftAxisX;
	static float leftAxisY;

	static float rightAxisX;
	static float rightAxisY;
	////////////////////////////////////////////


	/// Mouse Input ///////////////////////////	
	static double lastMouseX;
	static double lastMouseY;

	static double currentMouseX;
	static double currentMouseY;

	static double mouseX; //yaw
	static double mouseY; //pitch

	static double mouseSensitivity;

	static bool firstInput;
	////////////////////////////////////////////

	// Keyboard Mapping ///////////////////////
	static bool keyEventMap[512];
	//////////////////////////////////////////

	/// Joystick input
	static bool gamepad[4];

	static float leftJoySensitivity;
	static float rightJoySensitivity;

	static float deadZone;
	////////////////////////////////////////////

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int
		mods);

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	static void joystick_callback(int jid, int event);

	static void update();
};

