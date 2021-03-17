#pragma once
#include <vector>

#include "Entity.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "FileLoader.hpp"

using std::vector;

class Model {
	protected:
		vector<Mesh*> meshList;
		vector<Material*> materialList;

		bool hasTransparency;
	public:
		Model();
		Model(const Model& object);
		Model(const vector<Mesh*>& _meshList, const vector<Material*>& _materialList, bool hasTrasnparency);
		//Model(const char* filename);

		~Model();

		//void load(const char* filename);

		void addMesh(Mesh* mesh, Material* material);

		const Material& getMaterial(size_t index) const;
		Material& getMaterial(size_t index);
		
		size_t getMeshCount();
		size_t getMaterialCount();
		
		Mesh* getMesh(const int& pos);

		bool isTransparent();
};

