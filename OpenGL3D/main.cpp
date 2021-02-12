#include "OpenGLDebugger.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Mesh.h"
#include "GLSLShader.h"
#include "GLRender.h"
#include "Triangle.h"
#include "Cube.h"
#include "State.h"
#include "Input.h"
#include "World.h"
#include "GLTexture.h"

glm::uint32 Mesh::globalMeshID = 0;

int main(void) {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	glfwSetKeyCallback(window, Input::keyCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetCursorPosCallback(window, Input::cursor_position_callback);
	glfwSetJoystickCallback(Input::joystick_callback);


	GLRender* render = new GLRender();

	if (!render->init())
		return -1;

	State::defaultShader = new GLSLShader(shaderPath + "vertex.shader", shaderPath + "fragment.shader");

	Model cube((meshPath + "asian_town.msh").c_str());
	cube.setSize(glm::vec3(10.f, 10.f, 10.f));
	//Cube cube;
	render->setupObj(&cube);

	World* world = new World();
	world->addObject(&cube);

	world->addCamera(new Camera(glm::vec3(.0f, 1.f, 3.f),  // position
		glm::vec3(.0f, 1.f, .0f), // up 
		glm::vec3(.0f, 0.f, 1.f), // lookAt
		glm::vec3(1.f, 1.f, 1.f), // clearColor
		glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f))); // projection
	world->setActiveCamera(0);

	double oldTimeSinceStart = 0;
	while (!glfwWindowShouldClose(window)) {
		double timeSinceStart = glfwGetTime();
		double deltaTime = timeSinceStart - oldTimeSinceStart;
		oldTimeSinceStart = timeSinceStart;

		//limpiar buffer de color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world->update(deltaTime);
		render->drawWorld(world);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();

		Input::update();
	}

	glfwTerminate();

	return 0;
}