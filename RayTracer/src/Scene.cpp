#include "Scene.h"

Scene::Scene(const vec3 &ambientLight, const vec3 &backgroundColor) : ambientLight(ambientLight), backgroundColor(backgroundColor) {
}

Scene::~Scene() {
	for (auto it = objects.begin(); it != objects.end(); it++)
		delete (*it);

	for (auto it = lights.begin(); it != lights.end(); it++)
		delete (*it);
}

void Scene::addObject(Object *object) {
	objects.push_back(object);
}

void Scene::addLight(Light *light) {
	lights.push_back(light);
}