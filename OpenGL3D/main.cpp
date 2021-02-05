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
#include "World.h"
#include "GLTexture.h"
#include "FileLoader.h"

glm::uint32 Mesh::globalMeshID = 0;

std::string parseShader(const std::string& filepath) {
	std::fstream stream(filepath);

	std::string line;
	std::stringstream ss;
	
	while (getline(stream, line)) {
		ss << line << '\n';
	}

	return ss.str();
}

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

	glfwSetKeyCallback(window, State::keyCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetCursorPosCallback(window, State::cursor_position_callback);

	GLRender* render = new GLRender();
	
	if (!render->init())
		return -1;

	State::defaultShader = new GLSLShader(parseShader(shaderPath + "vertex.shader"), parseShader(shaderPath + "fragment.shader"));

	Object3D cube((meshPath + "asian_town.msh").c_str());
	cube.setSize(glm::vec3(10.f, 10.f, 10.f));
	render->setupObj(&cube);

	World* world = new World();
	world->addObject(&cube);
	
	world->addCamera(new Camera(glm::vec3(.0f, 1.f, 3.f),  // position
				                glm::vec3(.0f, 1.f, .0f), // up 
								glm::vec3(.0f, 0.f, 1.f), // lookAt
								glm::vec3(1.f, 1.f, 1.f), // clearColor
								glm::perspective(glm::radians(75.0f), 4.0f / 3.0f, 0.1f, 100.0f))); // projection
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
	}

	glfwTerminate();

	return 0;
}