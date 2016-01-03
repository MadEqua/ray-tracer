#pragma once

#include "Object.h"
#include "Light.h"
#include <vector>

using namespace std;

class Scene {
private:
	//typedef unique_ptr<Object> objectPtr;
	//typedef unique_ptr<Light> lightPtr;

	vector<Object*> objects;
	vector<Light*> lights;

public:
	vec3 ambientLight;
	vec3 backgroundColor;

	Scene(const vec3 &ambientLight, const vec3 &backgroundColor);
	~Scene();

	void addObject(Object *object);
	void addLight(Light *light);

	inline const vector<Object*> & getObjects() const { return objects; }
	inline const vector<Light*> & getLights() const { return lights; }
};