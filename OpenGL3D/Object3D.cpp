#include "Object3D.h"
#include "pugixml.hpp"

Object3D::Object3D() {}

Object3D::Object3D(const Object3D& object) : 
	meshList(object.meshList),
	materialList(object.materialList),
	Entity(object) 
	{}

Object3D::Object3D(const char* filename) {
	load(filename);
}

void Object3D::load(const char* filename) {
	std::string path = FileLoader<void*>::extractPath(filename);

	if (path == "")
		exit(-1);

	pugi::xml_document meshXml;
	pugi::xml_parse_result result = meshXml.load_file(filename);

	if (result) {
		pugi::xml_node buffers = meshXml.child("mesh").child("buffers");
		pugi::xml_node bufferNode = buffers.child("buffer");
	
		do {
			std::string textureName = bufferNode.child("material").child("texture").text().as_string();

			GLTexture* texture = new GLTexture((texturePath + textureName).c_str());
			Material* material = new Material(texture);

			std::vector<glm::int32> indices = FileLoader<glm::int32>::splitString(std::string(bufferNode.child("indices").text().as_string()), ',');
			std::vector<float> vertices = FileLoader<float>::splitString(std::string(bufferNode.child("coords").text().as_string()), ',');
			std::vector<float> textCoords = FileLoader<float>::splitString(std::string(bufferNode.child("texCoords").text().as_string()), ',');

			int vertexCompCount = bufferNode.child("coords").attribute("vertexCompCount").as_int();
			int texCoordCompCount = bufferNode.child("texCoords").attribute("texCoordCompCount").as_int();
			Mesh3D* mesh = new Mesh3D();

			if ((vertices.size() / vertexCompCount) == (textCoords.size() / texCoordCompCount)) {
				auto itVt = vertices.begin();
				auto itTx = textCoords.begin();
				while (itVt != vertices.end()) {
					float x = *itVt; itVt++; float y = *itVt; itVt++; float z = *itVt; itVt++;
					glm::vec4 vertex(x, y, z, 1);

					float s = *itTx; itTx++; float t = *itTx; itTx++;
					glm::vec2 textCoord(s, t);

					mesh->addVertex(vertex_t(vertex, glm::vec4(1), textCoord));
				}
			} else {
				std::cout << "Invalid data: vertices and texture coordinates don't match!" << std::endl;
				exit(-1);
			}
		
			auto it = indices.begin();
			while (it != indices.end()) {
				int idx1 = *it; it++; int idx2 = *it; it++; int idx3 = *it; it++;
				mesh->addTriangleIdx(idx1, idx2, idx3);
			}
			
			addMesh(mesh, material);
		} while ((bufferNode = bufferNode.next_sibling("buffer")));
	} else {
		std::cout << "Xml failed to load, exiting." << std::endl;
		exit(-1);
	}

	pos = glm::vec3(0);
	rot = glm::vec3(0);
	size = glm::vec3(1);

	computeModelMtx();
}

Object3D::~Object3D() {}

void Object3D::addMesh(Mesh3D* mesh, Material* material) { 
	meshList.push_back(mesh); 
	materialList.push_back(material);
}

Mesh3D* Object3D::getMesh(const int& pos) { return meshList[pos]; }

const Material& Object3D::getMaterial(size_t pos) const { return *materialList[pos]; }
Material& Object3D::getMaterial(size_t pos) { return *materialList[pos]; }

int Object3D::getMeshCount() { return meshList.size(); }
int Object3D::getMaterialCount() { return materialList.size(); }

void Object3D::step(float deltaTime) {
	computeModelMtx();
}


/*	if ((vertices.size() / vertexCompCount) == (textCoords.size() / texCoordCompCount)) {
			for (size_t i = 0; i < verticesCount; i++) {
				glm::vec4 vertex(vertices[i*3], vertices[(i *3) + 1], vertices[(i * 3) + 2], 1);
				glm::vec2 textCoord(textCoords[i*2], textCoords[(i*2) +1]);

				///std::cout << i * 3 << " " << (i * 3) + 1 << " " << i * 3 + 2 << " " << i * 2 << " " << (i * 2) + 1 << std::endl;

				mesh->addVertex(vertex_t(vertex, glm::vec4(1), textCoord));
			}
		} else {
			std::cout << "Invalid data, vertices and texture coordinates doesn't match!" << std::endl;
			exit(-1);
		}*/