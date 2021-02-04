#pragma once
#include <vector>

#include "Entity.h"
#include "Mesh3D.h"
#include "Material.h"
#include "FileLoader.h"

using std::vector;

class Object3D : public Entity {
	protected:
		vector<Mesh3D*> meshList;
		vector<Material*> materialList;

	public:
		Object3D();
		Object3D(const Object3D& object);
		Object3D(const char* filename);
		~Object3D();

		void load(const char* filename);

		void addMesh(Mesh3D* mesh, Material* material);

		const Material& getMaterial(size_t index) const;
		Material& getMaterial(size_t index);
		
		int getMeshCount();
		int getMaterialCount();
		
		Mesh3D* getMesh(const int& pos);

		virtual void step(float deltaTime);
};

