#include "Plane.h"

#include <glm/glm.hpp>
#include <cmath>
#include "Utils.h"

#include <iostream>

Plane::Plane(const vec3 &position, const vec3 &normal, const vec3 &tangent, const Material &material) :
	Object(position, material), normal(normalize(normal)), tangent(normalize(tangent)), binormal(cross(normal, tangent)) {
}

const Intersection Plane::intersect(const Ray &ray) const {
	Intersection intersection(&ray, this, -1.0f);

	float denominator = dot(normal, ray.dir);

	//if denominator is almost 0 then Ray is pratically parallel to Plane
	if (abs(denominator) > Utils::EPSILON_FLOAT) {
		float num = dot(normal, ray.orig - position);
		intersection.rayT = - num / denominator;
	}
	return intersection;
}

const SurfacePointData Plane::getSurfacePointData(const Intersection &intersection) const {
	const vec3 &surfacePoint = intersection.getIntersectionPosition();
	vec3 localCoords = surfacePoint - position;
	vec2 texCoords = { dot(localCoords, tangent), dot(localCoords, binormal) };
	return{ normal, texCoords, surfacePoint, tangent, binormal };
}