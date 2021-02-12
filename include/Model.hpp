#pragma once
#include <vector>

#include "Entity.h"
#include "Mesh.h"
#include "Material.h"
#include "FileLoader.h"

using std::vector;

class Model : public Entity {
	protected:
		vector<Mesh*> meshList;
		vector<Material*> materialList;

	public:
		Model();
		Model(const Model& object);
		Model(const char* filename);
		~Model();

		void load(const char* filename);

		void addMesh(Mesh* mesh, Material* material);

		const Material& getMaterial(size_t index) const;
		Material& getMaterial(size_t index);
		
		int getMeshCount();
		int getMaterialCount();
		
		Mesh* getMesh(const int& pos);

		virtual void step(float deltaTime);
};

