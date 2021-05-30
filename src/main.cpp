#include "OpenGLDebugger.hpp"

#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>

#include "Mesh.hpp"
#include "GLSLShader.hpp"
#include "GLRender.hpp"
#include "Cube.hpp"
#include "State.hpp"
#include "Input.hpp"
#include "World.hpp"
#include "GLTexture.hpp"
#include "SpotLight.hpp"
#include "DirectionalLight.hpp"
#include "AssetManager.hpp"
#include "Plane.hpp"

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

	srand(time(NULL));

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
	World* world = new World();

	if (!render->init())
		return -1;
	
	GLSLShader* shader = new GLSLShader(shaderPath + "vertex.shader", shaderPath + "fragment.shader");

	if (!State::initialize(shader)) {
		std::cerr << "Aborting" << std::endl;
		return -1;
	}

	Plane* plane = new Plane(1, State::defaultMaterial);

	GLTexture* landscape = new GLTexture(texturePath + "landscape.jfif");

	Material* mat = new Material(landscape, &State::blackMaterial->getSpecularMap(), &State::blackMaterial->getEmissiveMap(), .0f, false);
	plane->removeComponent<Material>();
	plane->addComponent<Material>(mat);	

	DirectionalLight* light = new DirectionalLight();
	world->addLight(light);
	world->addObject(plane);
	render->setupObj(plane);
	
	//for (auto model : AssetManager::modelHash)
		//render->setupObj(model.second);
	
	Camera camera;
	camera.setPos(glm::vec4(0, 1, 1, 1));

	world->addCamera(&camera);
	world->setActiveCamera(0);

	double oldTimeSinceStart = 0;
	while (!glfwWindowShouldClose(window)) {
		double timeSinceStart = glfwGetTime();
		double deltaTime = timeSinceStart - oldTimeSinceStart;
		oldTimeSinceStart = timeSinceStart;

		//limpiar buffer de color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Camera* camera = world->getCamera(world->getActiveCamera());

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