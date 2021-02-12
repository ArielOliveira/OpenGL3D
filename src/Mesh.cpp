#include "Mesh.hpp"

Mesh::Mesh() {
	globalMeshID++;

	meshID = globalMeshID;

	colorRGB = glm::vec3(1, 1, 1);

	vVertList = new vector<vertex_t>();
	vIdxList = new vector<glm::int32>();
}

Mesh::Mesh(vector<vertex_t>* vertexList, vector<glm::int32>* indexList, int vertexCount, int textCount) :
	vVertList(vertexList), vIdxList(indexList) {
	globalMeshID++;
	meshID = globalMeshID;
	colorRGB = glm::vec3(1, 1, 1);

	this->vertexCount = vertexCount;
	this->textCount = textCount; 
}

Mesh::~Mesh() {
	delete vVertList;
	delete vIdxList;
}

void Mesh::setVertexCount(const int& count) { this->vertexCount = count; }
void Mesh::setTextCount(const int& count) { this->textCount = count; }

const int Mesh::getVertexCount() const { return vertexCount; }
const int Mesh::getTextCount() const { return textCount; }

glm::uint32 Mesh::getMeshID() { return meshID; }

void Mesh::addVertex(const vertex_t& vertex) { vVertList->push_back(vertex); }

void Mesh::addTriangleIdx(const glm::int32& v1, const glm::int32& v2, const glm::int32& v3) {
	vIdxList->push_back(v1);
	vIdxList->push_back(v2);
	vIdxList->push_back(v3);
}

vector<vertex_t>* Mesh::getVertList() { return vVertList; }
vector<glm::int32>* Mesh::getTriangleIdxList() { return vIdxList; }

void Mesh::setColorRGB(float r, float g, float b) { colorRGB = glm::vec3(r, g, b); }
glm::vec3 Mesh::getColorRGB() { return colorRGB; }
