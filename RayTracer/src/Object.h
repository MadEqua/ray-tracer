#pragma once

#include "Ray.h"
#include "SurfacePointData.h"
#include "Material.h"

#include <glm/glm.hpp>

using namespace glm;

//Resolving circular dependence
class Intersection;

class Object {

protected:
	const Material &material;
	vec3 position;

public:
	Object(const vec3 &position, const Material &material);
	Object(const Material &material);

	virtual const Intersection intersect(const Ray &ray) const = 0;
	virtual const SurfacePointData getSurfacePointData(const Intersection &intersection) const = 0;

	inline const Material& getMaterial() const { return material; }
};