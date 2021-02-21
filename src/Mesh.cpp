#include "Mesh.hpp"

Mesh::Mesh() {
	globalMeshID++;

	meshID = globalMeshID;

	vVertList = new vector<vertex_t>();
	vIdxList = new vector<glm::int32>();
}

Mesh::Mesh(const Mesh& mesh) :
	vertexCount(mesh.vertexCount),
	textCount(mesh.textCount) {
	globalMeshID++;

	meshID = globalMeshID;

	vVertList = new vector<vertex_t>(mesh.vVertList->begin(), mesh.vVertList->end());
	vIdxList = new vector<glm::int32>(mesh.vIdxList->begin(), mesh.vIdxList->end());
}

Mesh::Mesh(vector<vertex_t>* vertexList, vector<glm::int32>* indexList, int vertexCount, int textCount) :
	vVertList(vertexList), vIdxList(indexList) {
	globalMeshID++;
	meshID = globalMeshID;

	this->vertexCount = vertexCount;
	this->textCount = textCount; 
}

Mesh::~Mesh() {
	delete vVertList;
	delete vIdxList;

	globalMeshID--;
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
