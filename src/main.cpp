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
#include "PointLight.hpp"

glm::uint32 Mesh::globalMeshID = 0;

std::string directory;
World* world;

Mesh* processMesh(aiMesh *mesh, const aiScene *scene) {
    Mesh* myMesh = new Mesh();
	
	myMesh->setVertexCount(4);
	myMesh->setTextCount(2);

    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        glm::vec4 position;
		position.x = mesh->mVertices[i].x;
		position.y = mesh->mVertices[i].y;
		position.z = mesh->mVertices[i].z;
		position.w = 1;
        
		glm::vec4 normal;
		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;
		normal.w = 0;
		
		glm::vec2 texture(0);
		if (mesh->mTextureCoords[0]) {
			texture.x = mesh->mTextureCoords[0][i].x;
			texture.y = mesh->mTextureCoords[0][i].y;
		}

		myMesh->addVertex(vertex_t{position, normal, texture});
    }
    if (mesh->mFaces->mNumIndices == 3) {
		for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
    		aiFace face = mesh->mFaces[i];
			myMesh->addTriangleIdx(face.mIndices[0], face.mIndices[1], face.mIndices[2]);	
		}
	}  else {
		std::cout << "Invalid index number for a triangle" << std::endl;
		exit(-1);
	}

    // process material
    if(mesh->mMaterialIndex >= 0) {
        
    }
	
    return myMesh;
}  

void processNode(aiNode *node, const aiScene *scene) {
	Model model;
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
		model.addMesh(processMesh(mesh, scene), new Material());
    }
	world->addObject(new Model(model));			
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}  

	void loadModel(string path) {
    		Assimp::Importer import;
    		const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    		if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        		return;
			}

    		directory = path.substr(0, path.find_last_of('/'));

    		processNode(scene->mRootNode, scene);
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
	GLTexture* texture = new GLTexture(State::whiteMap, glm::vec2(1));
	State::initialize(shader, texture);
	world = new World();
	//Model cube((meshPath + "asian_town.msh").c_str());
	//cube.setSize(glm::vec3(10.f, 10.f, 10.f));
	

	//loadModel(meshPath + "stanford-bunny.obj");
	//loadModel(meshPath + "cube-3d-shape.obj");

	Cube cube(Material(new GLTexture((texturePath + "crate_diffuse.png").c_str(), 0),
					   new GLTexture((texturePath + "crate_specular.png").c_str(), 1),
					   new GLTexture((texturePath + "matrix.jpg").c_str(), 2),
					   32.f));
	cube.setPos(glm::vec4(-2.f, .0f, .0f, 1.f));
	Cube anotherCube(cube);
	anotherCube.setPos(glm::vec4(2.f, .0f, .0f, 1.f));
	PointLight* light = new PointLight();
	world->addLight(light);
	world->getLight(0)->setPos(glm::vec4(.0f, 2.f, 0.0f, 1));
	//world->getLight(0)->setPos(glm::vec4(-.2f, -1.f, -0.3f, 0));
	world->addObject(&cube);
	world->addObject(&anotherCube);

	for (int i = 0; i < world->getNumObjects(); i++)
		render->setupObj(world->getObject(i));

	for (int i = 0; i < world->getNumLights(); i++)
		render->setupObj(world->getLight(i));

	world->addCamera(new Camera(glm::vec4(.0f, 1.f, 3.f, 1),  // position
		glm::vec3(.0f, 1.f, .0f), // up 
		glm::vec3(.0f, 0.f, 1.f), // lookAt
		glm::vec3(.0f, .0f, .1f), // clearColor
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