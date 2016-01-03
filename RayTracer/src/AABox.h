#pragma once

#include "Object.h"
#include "Material.h"
#include "Intersection.h"
#include "SurfacePointData.h"

#include <glm\vec3.hpp>

using namespace glm;

class AABox : public Object
{
public:
	AABox(const vec3 &center, const vec3 &dimension, const Material &material);
	AABox(const vec3 &center, const vec3 &min, const vec3 max, const Material &material);
	~AABox();

	const Intersection intersect(const Ray &ray) const;
	const SurfacePointData getSurfacePointData(const Intersection &intersection) const;

private:
	vec3 min;
	vec3 max;
};

