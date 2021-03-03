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

struct MeshPair {
	Mesh* mesh;
	Material* material;
};

glm::uint32 Mesh::globalMeshID = 0;

std::string directory;
World* world;

GLTexture* loadTextures(aiMaterial* material, aiTextureType type, string typeName) {
	//unsigned char* textureAtlas = 0;
	//glm::ivec2 atlasSize(0);
	int atlasSizeDivision = material->GetTextureCount(type);
	//int atlasChannels;

	//vector<std::string> textureNames;

	if (atlasSizeDivision == 0)
		return nullptr;

	if (atlasSizeDivision > 1) {
		std::cout << "Can't deal with multiple textures of the same type" << std::endl;
		exit(-1);
	}

	aiString name;
	glm::ivec2 size;
	int channels;
	GLTexture* glTexture = nullptr;

	material->GetTexture(type, 0, &name);

	auto it = AssetManager::loadedTextures.find(name.C_Str());
	unsigned char* texture;
	
	if (it != AssetManager::loadedTextures.end()) {
		return State::textureHash[it->second];
	} else {
		texture = AssetManager::textureFromFile(name.C_Str(), texturePath, size, channels);
		glTexture = new GLTexture(texture, size, 1, channels);
		AssetManager::loadedTextures[name.C_Str()] = glTexture->getId();
		State::textureHash[glTexture->getId()] = glTexture;
		return glTexture;
	}


	/*for (int i = 0; i < atlasSizeDivision; i++) {
		glm::ivec2 oldAtlasSize = atlasSize;

		aiString name;
		glm::ivec2 size;
		int channels;

		material->GetTexture(type, i, &name);

		auto it = AssetManager::loadedTextures->find(name.C_Str());
		unsigned char* texture;
		if (it != AssetManager::loadedTextures->end()) {
				
		}
		
		texture = AssetManager::textureFromFile(name.C_Str(), texturePath, size, channels);

		textureNames.push_back(name.C_Str());
		
		atlasSize.x += size.x;
		atlasSize.y += size.y;
		atlasChannels = channels;

		unsigned char* newTextureAtlas = new unsigned char[atlasSize.x*atlasSize.y];

		int oldSize = oldAtlasSize.x*oldAtlasSize.y;
		int newSize = atlasSize.x*atlasSize.y;
		int count = 0;

		for (int j = 0; j < oldSize; j++)
			newTextureAtlas[j] = textureAtlas[j];

		for (int k = oldSize; k < newSize; k++) 
			newTextureAtlas[k] = texture[count++];

		delete textureAtlas;

		AssetManager::freeSTBI(texture);
		textureAtlas = newTextureAtlas;

		if ((atlasSizeDivision > 1) && ((atlasSizeDivision % 2) != 0))
			std::cout << "Incomplete atlas" << std::endl;
	}*/
	
	//State::textureHash[]

	//return new GLTexture(textureAtlas, atlasSize, atlasSizeDivision);
}

MeshPair processMesh(aiMesh *mesh, const aiScene *scene) {
    Mesh* myMesh = new Mesh();
	Material* material = new Material();

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
        aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

		GLTexture* diffuse = loadTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse");
		if (diffuse)
			material->setDiffuseMap(diffuse);

		GLTexture* specular = loadTextures(mat, aiTextureType_SPECULAR, "texture_specular");
		if (specular)
			material->setSpecularMap(specular);
    }

    return {myMesh, material};
}  

void processNode(aiNode *node, const aiScene *scene) {
	Model* model = new Model();
    // process all the node's meshes (if any)
	std::cout << node->mNumChildren << std::endl;
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
		MeshPair pair = processMesh(mesh, scene);
		model->addMesh(pair.mesh, pair.material);
    }
	model->setSize(glm::vec4(10, 10, 10, 1));
	model->setPos(glm::vec4(10, 0, -5, 1));
	world->addObject(model);			
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
	GLTexture* texture = new GLTexture(State::whiteMap, glm::vec2(1), 1);
	State::initialize(shader, texture);
	world = new World();

	Cube cube(Material(new GLTexture((texturePath + "crate_diffuse.png").c_str()),
					   new GLTexture((texturePath + "crate_specular.png").c_str()),
					   new GLTexture((texturePath + "matrix.jpg").c_str()),
					   32.f));
	cube.setPos(glm::vec4(-2.f, .0f, .0f, 1.f));
	Cube anotherCube(cube);
	anotherCube.setPos(glm::vec4(2.f, .0f, .0f, 1.f));

	loadModel(meshPath + "backpack.obj");
	

	DirectionalLight* light = new DirectionalLight();
	PointLight* pointLight = new PointLight();
	PointLight* pointLight2 = new PointLight(*pointLight);
	PointLight* pointLight3 = new PointLight(*pointLight);
	SpotLight* spotLight = new SpotLight();
	
	pointLight2->setPos(glm::vec4(-4.f, .0f, .0f, 1.f));
	pointLight3->setPos(glm::vec4(2.0f, .0f, -2.f, 1.f));

	world->addLight(light);
	world->addLight(pointLight);
	world->addLight(pointLight2);
	world->addLight(pointLight3);
	world->addLight(spotLight);

	//world->addObject(&cube);
	//world->addObject(&anotherCube);

	//////////////////////////////////////////////
		/*glm::ivec2 size;
		int channels;
		
		unsigned char* test = AssetManager::textureFromFile("matrix.jpg", texturePath, size, channels);

		std::cout << size.x << " " << size.y << " " << channels << std::endl;

		AssetManager::freeSTBI(test);*/

	/////////////////////////////////////////////

	for (int i = 0; i < world->getNumObjects(); i++)
		render->setupObj(world->getObject(i));

	for (int i = 0; i < world->getNumLights(); i++)
		render->setupObj(world->getLight(i));

	world->addCamera(new Camera(glm::vec4(.0f, 1.f, 3.f, 1),  // position
		glm::vec3(.0f, 1.f, .0f), // up 
		glm::vec3(.0f, 0.f, 1.f), // lookAt
		glm::vec3(light->getAmbient().x, light->getAmbient().y, light->getAmbient().z), // clearColor
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