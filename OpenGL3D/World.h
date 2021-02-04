#pragma once
#include "Object3D.h"
#include "Camera.h"

class World {
	private:
		std::vector<Object3D*> objs;
		std::vector<Camera*> cameras;

		int activeCamera;

	public:
		World();

		void addObject(Object3D* obj);
		void addCamera(Camera* Cam);

		void removeObject(Object3D* obj);
		void removeCamera(Camera* cam);

		size_t getNumObjects();
		size_t getNumCameras();

		Object3D* getObject(size_t index);
		Camera* getCamera(size_t index);

		
		void setActiveCamera(size_t index);
		int getActiveCamera();

		void update(float deltaTime);
};

