#include "OpenGLDebugger.hpp"

#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Mesh.hpp"
#include "GLSLShader.hpp"
#include "GLRender.hpp"
#include "Triangle.hpp"
#include "Cube.hpp"
#include "State.hpp"
#include "Input.hpp"
#include "World.hpp"
#include "GLTexture.hpp"
#include "SpotLight.hpp"
#include "DirectionalLight.hpp"
#include "AssetManager.hpp"
#include "Plane.hpp"

glm::uint32 Mesh::globalMeshID = 0;

std::string directory;
World* world;

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

	GLSLShader* shader = new GLSLShader(shaderPath + "vertex.shader", shaderPath + "fragment.shader");
	GLTexture* texture = new GLTexture(State::whiteMap, glm::vec2(1), 1);
	State::initialize(shader, texture);

	world = new World();
	Plane* plane = new Plane();
	plane->setSize(glm::vec4(10, 1, 10, 1));
	world->addObject(plane);
	world->addObject(AssetManager::loadModel(meshPath + "backpack.obj"));
	
	DirectionalLight* light = new DirectionalLight();
	SpotLight* spotLight = new SpotLight();

	world->addLight(light);
	//world->addLight(spotLight);

	for (int i = 0; i < world->getNumObjects(); i++)
		render->setupObj(world->getObject(i));

	for (int i = 0; i < world->getNumLights(); i++)
		render->setupObj(world->getLight(i));

	world->addCamera(new Camera(glm::vec4(.0f, 1.f, 3.f, 1),  // position
		glm::vec3(.0f, 1.f, .0f), // up 
		glm::vec3(.0f, 0.f, 1.f), // lookAt
		glm::vec3(0, 0, 0), // clearColor
		glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f))); // projection
	world->setActiveCamera(0);

	double oldTimeSinceStart = 0;
	while (!glfwWindowShouldClose(window)) {
		double timeSinceStart = glfwGetTime();
		double deltaTime = timeSinceStart - oldTimeSinceStart;
		oldTimeSinceStart = timeSinceStart;

		//limpiar buffer de color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Camera* camera = world->getCamera(world->getActiveCamera());

		spotLight->setPos(camera->getPos());
		spotLight->setRot(camera->getRot());

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