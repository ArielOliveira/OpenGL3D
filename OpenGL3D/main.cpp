#include "OpenGLDebugger.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Mesh3D.h"
#include "GLSLShader.h"
#include "GLRender.h"
#include "Triangle.h"
#include "Cube.h"
#include "State.h"
#include "World.h"
#include "GLTexture.h"

glm::uint32 Mesh3D::globalMeshID = 0;

GLSLShader* State::defaultShader = nullptr;
glm::mat4 State::projectionMatrix = glm::mat4(1);
glm::mat4 State::viewMatrix = glm::mat4(1); 
glm::mat4 State::modelMatrix = glm::mat4(1);
char State::keybEvent[512];

double State::lastMouseX = 0;
double State::lastMouseY = 0;

double State::xRoll = 0;
double State::yRoll = 0;

bool State::firstInput = true;

typedef enum shaderType {
	NONE = -1, VERTEX = 0, FRAGMENT = 1
} shaderType;

typedef struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
} shaderProgramSource;

shaderProgramSource parseShader(const std::string& filepath) {
	std::fstream stream(filepath);

	std::string line;
	std::stringstream ss[2];
	shaderType type = shaderType::NONE;
	
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				type = shaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = shaderType::FRAGMENT;
		}
		else {
			ss[int(type)] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
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
	glfwSetCursorPosCallback(window, State::cursor_position_callback);

	GLRender* render = new GLRender();
	
	if (!render->init())
		return -1;

	shaderProgramSource source = parseShader("Shader.shader");
	State::defaultShader = new GLSLShader(source.VertexSource, source.FragmentSource);

	Object3D cube("../data/asian_town.msh");
	cube.setSize(glm::vec3(10.f, 10.f, 10.f));
	//cube.setPos(glm::vec3(.0f, .0f, .0f)); 
	render->setupObj(&cube);

	World* world = new World();
	world->addObject(&cube);

	/*for (int x = -3; x <= 3; x += 3) {
		for (int z = -6; z <= 0; z += 3) {
			cube.setPos(glm::vec3(x, 0.0f, z));
			cubes->push_back(cube);
		}
	}
	for (auto& cube : *cubes)
		world->addObject(&cube);*/
	
	world->addCamera(new Camera(glm::vec3(.0f, 1.f, 3.f),  // position
				                glm::vec3(.0f, 1.f, .0f), // up 
								glm::vec3(.0f, 0.f, 0.f), // lookAt
								glm::vec3(1.f, 1.f, 1.f))); // clearColor
	world->setActiveCamera(0);
	world->getCamera(0)->setProjection(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f));
	
	world->addObject(&cube);

	double oldTimeSinceStart = 0;
	while (!glfwWindowShouldClose(window)) {
		double timeSinceStart = glfwGetTime();
		double deltaTime = timeSinceStart - oldTimeSinceStart;
		oldTimeSinceStart = timeSinceStart;
		
		//std::cout << State::mouseInput.x << " " << State::mouseInput.y << std::endl;
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