#pragma once

#include "Object.h"
#include "Intersection.h"
#include "SurfacePointData.h"
#include "Ray.h"
#include <glm/vec3.hpp>

using namespace glm;

class Sphere : public Object {
private:
	float radius;

public:
	Sphere(const vec3 &position, const float radius, Material &material);

	const Intersection intersect(const Ray &ray) const;
	const SurfacePointData getSurfacePointData(const Intersection &intersection) const;
};