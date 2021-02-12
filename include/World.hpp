#pragma once
#include "Model.h"
#include "Camera.h"

class World {
	private:
		std::vector<Model*> objs;
		std::vector<Camera*> cameras;

		int activeCamera;

	public:
		World();

		void addObject(Model* obj);
		void addCamera(Camera* Cam);

		void removeObject(Model* obj);
		void removeCamera(Camera* cam);

		size_t getNumObjects();
		size_t getNumCameras();

		Model* getObject(size_t index);
		Camera* getCamera(size_t index);

		
		void setActiveCamera(size_t index);
		int getActiveCamera();

		void update(float deltaTime);
};

