#include "Sphere.h"

#include <glm/glm.hpp>
#include <cmath>
#include "Utils.h"

Sphere::Sphere(const vec3 &position, const float radius, Material &material) : Object(position, material), radius(radius) {
}

const Intersection Sphere::intersect(const Ray &ray) const
{ 
	Intersection intersection(&ray, this, -1.0f);

	// analytic solution
	vec3 L = ray.orig - position;
	float a = dot(ray.dir, ray.dir);
	float b = 2 * dot(ray.dir, L);
	float c = dot(L, L) - (radius * radius);

	float t0, t1;

	if (!Utils::solveQuadratic(a, b, c, t0, t1)) 
		return intersection;

	if (t0 < 0) {
		t0 = t1;
		if (t0 < 0) 
			return intersection;
	}

	intersection.rayT = t0;
	return intersection;
}

const SurfacePointData Sphere::getSurfacePointData(const Intersection &intersection) const {
	const vec3 &surfacePoint = intersection.getIntersectionPosition();
	vec3 localCoord = surfacePoint - position;
	vec3 normal = normalize(localCoord);

	float theta = atan2(localCoord.x, localCoord.z);
	float phi = acos(localCoord.y / radius);

	vec2 texCoords = { 0.5f + theta / (2.0f * Utils::PI), 1.0f - (phi / Utils::PI) };

	vec3 tangent(cos(theta) * cos(phi), cos(theta) * sin(phi), -sin(theta));
	vec3 bitangent(-sin(phi), cos(phi), 0);

	return{ normal, texCoords, surfacePoint, tangent, bitangent};
}