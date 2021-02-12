#include "Cube.hpp"

Cube::Cube() {
	Material* material = new Material(new GLTexture((texturePath + "front.png").c_str()), nullptr);

	Mesh* front = new Mesh();
	
	front->setVertexCount(4);
	front->setTextCount(2);

	front->addVertex(vertex_t(glm::vec4(-.5f, -.5f, -.5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(.0f, .0f)));
	front->addVertex(vertex_t(glm::vec4(.5f, -.5f, -.5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(1.f, .0f)));
	front->addVertex(vertex_t(glm::vec4(.5f, .5f, -.5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(1.f, 1.f)));
	front->addVertex(vertex_t(glm::vec4(-.5f, .5f, -.5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(.0f, 1.f)));

	front->addTriangleIdx(0, 1, 2);
	front->addTriangleIdx(2, 3, 0);

	addMesh(front, material);

	Mesh* back = new Mesh();
	back->setVertexCount(4);
	back->setTextCount(2);

	back->addVertex(vertex_t(glm::vec4(-.5f, -.5f, .5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(.0f, .0f)));
	back->addVertex(vertex_t(glm::vec4(.5f, -.5f, .5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(1.f, .0f)));
	back->addVertex(vertex_t(glm::vec4(.5f, .5f, .5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(1.f, 1.f)));
	back->addVertex(vertex_t(glm::vec4(-.5f, .5f, .5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(.0f, 1.f)));

	back->addTriangleIdx(0, 1, 2);
	back->addTriangleIdx(2, 3, 0);

	addMesh(back, material);

	Mesh* left = new Mesh();

	left->setVertexCount(4);
	left->setTextCount(2);

	left->addVertex(vertex_t(glm::vec4(-.5f, -.5f, -.5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(.0f, .0f)));
	left->addVertex(vertex_t(glm::vec4(-.5f, .5f, -.5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(1.f, .0f)));
	left->addVertex(vertex_t(glm::vec4(-.5f, .5f, .5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(1.f, 1.f)));
	left->addVertex(vertex_t(glm::vec4(-.5f, -.5f, .5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(.0f, 1.f)));

	left->addTriangleIdx(0, 1, 2);
	left->addTriangleIdx(2, 3, 0);

	addMesh(left, material);

	Mesh* right = new Mesh();

	right->setVertexCount(4);
	right->setTextCount(2);

	right->addVertex(vertex_t(glm::vec4(.5f, -.5f, -.5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(.0f, .0f)));
	right->addVertex(vertex_t(glm::vec4(.5f, .5f, -.5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(1.f, .0f)));
	right->addVertex(vertex_t(glm::vec4(.5f, .5f, .5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(1.f, 1.f)));
	right->addVertex(vertex_t(glm::vec4(.5f, -.5f, .5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(.0f, 1.f)));

	right->addTriangleIdx(0, 1, 2);
	right->addTriangleIdx(2, 3, 0);

	addMesh(right, material);

	Material* material2 = new Material(new GLTexture((texturePath + "top.png").c_str()), nullptr);
	Mesh* top = new Mesh();

	top->setVertexCount(4);
	top->setTextCount(2);

	top->addVertex(vertex_t(glm::vec4(-.5f, .5f, -.5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(.0f, .0f)));
	top->addVertex(vertex_t(glm::vec4(.5f, .5f, -.5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(1.f, .0f)));
	top->addVertex(vertex_t(glm::vec4(.5f, .5f, .5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(1.f, 1.f)));
	top->addVertex(vertex_t(glm::vec4(-.5f, .5f, .5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(.0f, 1.f)));

	top->addTriangleIdx(0, 1, 2);
	top->addTriangleIdx(2, 3, 0);

	addMesh(top, material2);

	Mesh* bottom = new Mesh();

	bottom->setVertexCount(4);
	bottom->setTextCount(2);

	bottom->addVertex(vertex_t(glm::vec4(-.5f, -.5f, -.5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(.0f, .0f)));
	bottom->addVertex(vertex_t(glm::vec4(.5f, -.5f, -.5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(1.f, .0f)));
	bottom->addVertex(vertex_t(glm::vec4(.5f, -.5f, .5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(1.f, 1.f)));
	bottom->addVertex(vertex_t(glm::vec4(-.5f, -.5f, .5f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(.0f, 1.f)));

	bottom->addTriangleIdx(0, 1, 2);
	bottom->addTriangleIdx(2, 3, 0);

	addMesh(bottom, material2);

	setSize(glm::vec3(1.f, 1.f, 1.f));
	setPos(glm::vec3(.0f, .0f, .0f));
}
Cube::Cube(const Cube& cube) : Model(cube) {}

Cube::Cube(const char* filename) : Model(filename) {}

Cube::~Cube() {}
void Cube::step(float deltaTime) {
	//rot.x = fmodf(rot.x + glm::radians(32.0f) * deltaTime, glm::radians(360.0f));
	rot.y = fmodf(rot.y + glm::radians(32.0f) * deltaTime, glm::radians(360.0f));
	//rot.z = fmodf(rot.z + glm::radians(32.0f) * deltaTime, glm::radians(360.0f));
	
	Model::step(deltaTime);
}
