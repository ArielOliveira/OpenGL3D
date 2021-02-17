#include "World.hpp"

World::World() {
	activeCamera = 0;
}

void World::addObject(Model* obj) { objs.push_back(obj); }
void World::addCamera(Camera* cam) { cameras.push_back(cam); }
void World::addLight(Light* light) { lights.push_back(light); }

void World::removeObject(Model* obj) {
	auto it = std::find(objs.begin(), objs.end(), obj);
	
	if (it != objs.end())
		objs.erase(it);
}

void World::removeCamera(Camera* cam) {
	auto it = std::find(cameras.begin(), cameras.end(), cam);

	if (it != cameras.end())
		cameras.erase(it);
}

void World::removeLight(Light* light) {
	auto it = std::find(lights.begin(), lights.end(), light);

	if (it != lights.end())
		lights.erase(it);
}

size_t World::getNumObjects() { return objs.size(); }
size_t World::getNumCameras() { return cameras.size(); }
size_t World::getNumLights() { return lights.size(); }

Model* World::getObject(size_t index) { return objs[index]; }
Camera* World::getCamera(size_t index) { return cameras[index]; }
Light* World::getLight(size_t index) { return lights[index]; }

void World::setActiveCamera(size_t index) { activeCamera = index; }
int World::getActiveCamera() { return activeCamera; }

void World::update(float deltaTime) {
	for (auto& object : objs)
		object->step(deltaTime);
	for (auto& camera : cameras)
		camera->step(deltaTime);
	for (auto& light : lights)
		light->step(deltaTime);
}
