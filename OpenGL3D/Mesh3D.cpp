#include "Mesh3D.h"

Mesh3D::Mesh3D() {
	globalMeshID++;

	meshID = globalMeshID;

	colorRGB = glm::vec3(1, 1, 1);

	vVertList = new vector<vertex_t>();
	vIdxList = new vector<glm::int32>();
}

Mesh3D::Mesh3D(vector<vertex_t>* vertexList, vector<glm::int32>* indexList) :
	vVertList(vertexList), vIdxList(indexList) {
	globalMeshID++;
	meshID = globalMeshID;
	colorRGB = glm::vec3(1, 1, 1);
}

Mesh3D::~Mesh3D() {
	delete vVertList;
	delete vIdxList;
}

glm::uint32 Mesh3D::getMeshID() { return meshID; }

void Mesh3D::addVertex(const vertex_t& vertex) { vVertList->push_back(vertex); }

void Mesh3D::addTriangleIdx(const glm::int32& v1, const glm::int32& v2, const glm::int32& v3) {
	vIdxList->push_back(v1);
	vIdxList->push_back(v2);
	vIdxList->push_back(v3);
}

vector<vertex_t>* Mesh3D::getVertList() { return vVertList; }
vector<glm::int32>* Mesh3D::getTriangleIdxList() { return vIdxList; }

void Mesh3D::setColorRGB(float r, float g, float b) { colorRGB = glm::vec3(r, g, b); }
glm::vec3 Mesh3D::getColorRGB() { return colorRGB; }
