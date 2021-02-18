#include "Cube.hpp"

Cube::Cube() : Model() {
	addMesh(makeCube(), new Material());
}

Cube::Cube(const Cube& cube) : Model(cube) {}

Cube::Cube(const char* filename) : Model(filename) {}

Cube::Cube(const Material& material) : Model() {
	addMesh(makeCube(), new Material(material));
}

Cube::~Cube() {}

Mesh* Cube::makeCube() {
	Mesh* mesh = new Mesh();

	//back face
	mesh->addVertex(vertex_t(glm::vec3(-.5f, -.5f, -.5f), glm::vec3(.0f, .0f, -1.f), glm::vec2(.0f, .0f)));
	mesh->addVertex(vertex_t(glm::vec3(.5f, -.5f, -.5f), glm::vec3(.0f, .0f, -1.f), glm::vec2(1.f, .0f)));
	mesh->addVertex(vertex_t(glm::vec3(.5f, .5f, -.5f), glm::vec3(.0f, .0f, -1.f), glm::vec2(1.f, 1.f)));
	mesh->addVertex(vertex_t(glm::vec3(-.5f, .5f, -.5f), glm::vec3(.0f, .0f, -1.f), glm::vec2(.0f, 1.f)));

	mesh->addTriangleIdx(0, 1, 2);
	mesh->addTriangleIdx(2, 3, 0);

	// front face
	mesh->addVertex(vertex_t(glm::vec3(-.5f, -.5f, .5f), glm::vec3(.0f, .0f, 1.f), glm::vec2(.0f, .0f)));
	mesh->addVertex(vertex_t(glm::vec3(.5f, -.5f, .5f), glm::vec3(.0f, .0f, 1.f), glm::vec2(1.f, .0f)));
	mesh->addVertex(vertex_t(glm::vec3(.5f, .5f, .5f), glm::vec3(.0f, .0f, 1.f), glm::vec2(1.f, 1.f)));
	mesh->addVertex(vertex_t(glm::vec3(-.5f, .5f, .5f), glm::vec3(.0f, .0f, 1.f), glm::vec2(.0f, 1.f)));
	
	mesh->addTriangleIdx(4, 5, 6);
	mesh->addTriangleIdx(6, 7, 4);
	
	// left face
	mesh->addVertex(vertex_t(glm::vec3(-.5f, -.5f, -.5f), glm::vec3(-1.f, .0f, .0f), glm::vec2(.0f, .0f)));
	mesh->addVertex(vertex_t(glm::vec3(-.5f, .5f, -.5f), glm::vec3(-1.f, .0f, .0f), glm::vec2(1.f, .0f)));
	mesh->addVertex(vertex_t(glm::vec3(-.5f, .5f, .5f), glm::vec3(-1.f, .0f, .0f), glm::vec2(1.f, 1.f)));
	mesh->addVertex(vertex_t(glm::vec3(-.5f, -.5f, .5f), glm::vec3(-1.f, .0f, .0f), glm::vec2(.0f, 1.f)));

	mesh->addTriangleIdx(8, 9, 10);
	mesh->addTriangleIdx(10, 11, 8);

	// right face
	mesh->addVertex(vertex_t(glm::vec3(.5f, -.5f, -.5f), glm::vec3(1.f, .0f, .0f), glm::vec2(.0f, .0f)));
	mesh->addVertex(vertex_t(glm::vec3(.5f, .5f, -.5f), glm::vec3(1.f, .0f, .0f), glm::vec2(1.f, .0f)));
	mesh->addVertex(vertex_t(glm::vec3(.5f, .5f, .5f), glm::vec3(1.f, .0f, .0f), glm::vec2(1.f, 1.f)));
	mesh->addVertex(vertex_t(glm::vec3(.5f, -.5f, .5f), glm::vec3(1.f, .0f, .0f), glm::vec2(.0f, 1.f)));


	mesh->addTriangleIdx(12, 13, 14);
	mesh->addTriangleIdx(14, 15, 12);


	// top face
	mesh->addVertex(vertex_t(glm::vec3(-.5f, .5f, -.5f), glm::vec3(.0f, 1.f, .0f), glm::vec2(.0f, .0f)));
	mesh->addVertex(vertex_t(glm::vec3(.5f, .5f, -.5f), glm::vec3(.0f, 1.f, .0f), glm::vec2(1.f, .0f)));
	mesh->addVertex(vertex_t(glm::vec3(.5f, .5f, .5f), glm::vec3(.0f, 1.f, .0f), glm::vec2(1.f, 1.f)));
	mesh->addVertex(vertex_t(glm::vec3(-.5f, .5f, .5f), glm::vec3(.0f, 1.f, .0f), glm::vec2(.0f, 1.f)));

		
	
	mesh->addTriangleIdx(16, 17, 18);
	mesh->addTriangleIdx(18, 19, 16);

	// bottom face
	mesh->addVertex(vertex_t(glm::vec3(-.5f, -.5f, -.5f), glm::vec3(.0f, -1.f, .0f), glm::vec2(.0f, .0f)));
	mesh->addVertex(vertex_t(glm::vec3(.5f, -.5f, -.5f), glm::vec3(.0f, -1.f, .0f), glm::vec2(1.f, .0f)));
	mesh->addVertex(vertex_t(glm::vec3(.5f, -.5f, .5f), glm::vec3(.0f, -1.f, .0f), glm::vec2(1.f, 1.f)));
	mesh->addVertex(vertex_t(glm::vec3(-.5f, -.5f, .5f), glm::vec3(.0f, -1.f, .0f), glm::vec2(.0f, 1.f)));

	
	mesh->addTriangleIdx(20, 21, 22);
	mesh->addTriangleIdx(22, 23, 20);

	mesh->setVertexCount(3);
	mesh->setTextCount(2);

	return mesh;
}

void Cube::step(float deltaTime) {
	//rot.z = fmodf(rot.z + glm::radians(32.0f) * deltaTime, glm::radians(360.0f));
	Model::step(deltaTime);
}
