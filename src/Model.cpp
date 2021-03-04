#include "Model.hpp"
#include "pugixml.hpp"

Model::Model() : Entity() 
	{}

Model::Model(const Model& object) : 
	meshList(object.meshList),
	materialList(object.materialList),
	Entity(object) 
	{}

Model::Model(const vector<Mesh*>& _meshList, const vector<Material*>& _materialList) :
	meshList(_meshList),
	materialList(_materialList)
	{}

Model::Model(const char* filename) {
	load(filename);
}

void Model::load(const char* filename) {
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
			
			GLTexture* texture = new GLTexture((texturePath + textureName));
			Material* material = new Material(texture, nullptr, nullptr, 32.f, State::defaultShader);

			std::vector<glm::int32> indices = FileLoader<glm::int32>::splitString(std::string(bufferNode.child("indices").text().as_string()), ',');
			std::vector<float> vertices = FileLoader<float>::splitString(std::string(bufferNode.child("coords").text().as_string()), ',');
			std::vector<float> textCoords = FileLoader<float>::splitString(std::string(bufferNode.child("texCoords").text().as_string()), ',');

			int vertexCompCount = bufferNode.child("coords").attribute("vertexCompCount").as_int();
			int texCoordCompCount = bufferNode.child("texCoords").attribute("texCoordCompCount").as_int();
			
			Mesh* mesh = new Mesh();
			
			mesh->setVertexCount(4);
			mesh->setTextCount(texCoordCompCount);

			if ((vertices.size() / vertexCompCount) == (textCoords.size() / texCoordCompCount)) {
				auto itVt = vertices.begin();
				auto itTx = textCoords.begin();
				while (itVt != vertices.end()) {
					float x = *itVt; itVt++; float y = *itVt; itVt++; float z = *itVt; itVt++;
					glm::vec4 vertex(x, y, z, 1);

					float u = *itTx; itTx++; float v = *itTx; itTx++;

					mesh->addVertex({vertex, glm::vec4(0), glm::vec2(u, v)});
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

	pos = glm::vec4(0, 0, 0, 1);
	rot = glm::vec4(0, 0, 0, 1);
	size = glm::vec4(1);

	computeModelMtx();
}

Model::~Model() {}

void Model::addMesh(Mesh* mesh, Material* material) { 
	meshList.push_back(mesh); 
	materialList.push_back(material);
}

Mesh* Model::getMesh(const int& pos) { return meshList[pos]; }

const Material& Model::getMaterial(size_t pos) const { return *materialList[pos]; }
Material& Model::getMaterial(size_t pos) { return *materialList[pos]; }

size_t Model::getMeshCount() { return meshList.size(); }
size_t Model::getMaterialCount() { return materialList.size(); }

void Model::step(float deltaTime) {
	computeModelMtx();
}