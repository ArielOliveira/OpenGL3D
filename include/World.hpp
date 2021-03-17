#pragma once
#include "Model.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include <gtx\norm.hpp>

#include <map>

class World {
	private:
		std::vector<Object*> objs;
		std::vector<Object*> transparentObjs;
		std::vector<Camera*> cameras;
		std::vector<Light*> lights;

		map<float, Object*> sortedTransparent;

		int activeCamera;
	public:
		World();

		void addObject(Object* obj);
		void addTransparentObject(Object* obj);
		void addCamera(Camera* Cam);
		void addLight(Light* light);

		void removeObject(Object* obj);
		void removeTransparentObject(Object* obj);
		void removeCamera(Camera* cam);
		void removeLight(Light* light);

		size_t getNumObjects();
		size_t getNumTransparentObjects();
		size_t getNumCameras();
		size_t getNumLights();

		Object* getObject(size_t index);
		Object* getTransparentObject(size_t index);
		map<float, Object*> getSortedTransparent();
		Camera* getCamera(size_t index);
		Light* getLight(size_t index);
	
		void setActiveCamera(size_t index);
		int getActiveCamera();

		void update(float deltaTime);
};

