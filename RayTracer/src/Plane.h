#pragma once

#include "Object.h"
#include "Intersection.h"
#include "SurfacePointData.h"
#include "Material.h"
#include "Ray.h"
#include <glm/vec3.hpp>

using namespace glm;

class Plane : public Object {
private:
	vec3 normal;
	vec3 tangent;
	vec3 binormal;

public:
	Plane(const vec3 &position, const vec3 &normal, const vec3 &tangent, const Material &material);

	const Intersection intersect(const Ray &ray) const;
	const SurfacePointData getSurfacePointData(const Intersection &intersection) const;
};