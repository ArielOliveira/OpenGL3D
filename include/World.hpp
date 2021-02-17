#pragma once
#include "Model.hpp"
#include "Camera.hpp"
#include "Light.hpp"

class World {
	private:
		std::vector<Model*> objs;
		std::vector<Camera*> cameras;
		std::vector<Light*> lights;

		int activeCamera;
	public:
		World();

		void addObject(Model* obj);
		void addCamera(Camera* Cam);
		void addLight(Light* light);

		void removeObject(Model* obj);
		void removeCamera(Camera* cam);
		void removeLight(Light* light);

		size_t getNumObjects();
		size_t getNumCameras();
		size_t getNumLights();

		Model* getObject(size_t index);
		Camera* getCamera(size_t index);
		Light* getLight(size_t index);
	
		void setActiveCamera(size_t index);
		int getActiveCamera();

		void update(float deltaTime);
};

