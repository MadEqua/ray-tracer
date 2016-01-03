#pragma once

#include "Ray.h"
#include "Object.h"
#include <glm/vec3.hpp>

using namespace glm;

class Intersection {
public:
	const Ray *ray;
	const Object *object;
	float rayT;

	//Triangle Only
	int triangleIndex;
	float u, v; //barycentric coords

	Intersection();
	Intersection(const Ray *ray, const Object *object, const float rayT);

	inline bool isIntersecting() const { return rayT >= 0; }
	inline const vec3 getIntersectionPosition() const { return ray->orig + ray->dir * rayT; }
};