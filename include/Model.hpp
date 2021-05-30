#pragma once
#include <vector>

#include "Entity.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "FileLoader.hpp"

using std::vector;

class Model {
	protected:
		vector<const Mesh*> meshList;
		vector<const Material*> materialList;

	public:
		Model();
		Model(const Model& object);
		Model(const vector<const Mesh*>& _meshList, const vector<const Material*>& _materialList);

		~Model();

		void addMesh(const Mesh* mesh, const Material* material);

		const Material& getMaterial(size_t index) const;
		
		size_t getMeshCount() const;
		size_t getMaterialCount() const;
		
		const Mesh* getMesh(const int& pos);

		bool isTransparent();
};

