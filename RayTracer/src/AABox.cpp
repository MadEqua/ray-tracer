#include "AABox.h"

#include "Utils.h"


AABox::AABox(const vec3 &center, const vec3 &dimensions, const Material &material) :
min(vec3(center.x - dimensions.x / 2.0f, center.y - dimensions.y / 2.0f, center.z - dimensions.z / 2.0f)),
max(vec3(center.x + dimensions.x / 2.0f, center.y + dimensions.y / 2.0f, center.z + dimensions.z / 2.0f)),
Object(center, material)
{
}

AABox::AABox(const vec3 &center, const vec3 &min, const vec3 max, const Material &material) : 
min(min), max(max), Object(center, material) {

}

AABox::~AABox()
{
}

const Intersection AABox::intersect(const Ray &ray) const {
	Intersection intersection(&ray, this, -1);

	float tmin = (min.x - ray.orig.x) / ray.dir.x;
	float tmax = (max.x - ray.orig.x) / ray.dir.x;

	if (tmin > tmax) 
		swap(tmin, tmax);

	float tymin = (min.y - ray.orig.y) / ray.dir.y;
	float tymax = (max.y - ray.orig.y) / ray.dir.y;

	if (tymin > tymax) 
		swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return intersection;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (min.z - ray.orig.z) / ray.dir.z;
	float tzmax = (max.z - ray.orig.z) / ray.dir.z;

	if (tzmin > tzmax) 
		swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return intersection;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	intersection.rayT = tmin > 0 ? tmin : tmax;
	return intersection;
}

const SurfacePointData AABox::getSurfacePointData(const Intersection &intersection) const {
	SurfacePointData data;

	const vec3 &surfacePoint = intersection.getIntersectionPosition();

	const float epsilon = 0.001f;

	if (Utils::floatEquals(surfacePoint.x, min.x, epsilon)) {
		data.normal = { -1, 0, 0 };
		data.tangent = {0, 0 , 1};
		data.bitangent = { 0, 1, 0 };
	}
	else if (Utils::floatEquals(surfacePoint.x, max.x, epsilon)) {
		data.normal = { 1, 0, 0 };
		data.tangent = { 0, 0, 1 };
		data.bitangent = { 0, 1, 0 };
	}
	else if (Utils::floatEquals(surfacePoint.y, min.y, epsilon)) {
		data.normal = { 0, -1, 0 };
		data.tangent = { 1, 0, 0 };
		data.bitangent = { 0, 0, 1 };
	}
	else if (Utils::floatEquals(surfacePoint.y, max.y, epsilon)){
		data.normal = { 0, 1, 0 };
		data.tangent = { 1, 0, 1 };
		data.bitangent = { 0, 0, 1 };
	}
	else if (Utils::floatEquals(surfacePoint.z, min.z, epsilon)) {
		data.normal = { 0, 0, -1 };
		data.tangent = { 1, 0, 0 };
		data.bitangent = { 0, 1, 0 };
	}
	else if (Utils::floatEquals(surfacePoint.z, max.z, epsilon)) {
		data.normal = { 0, 0, 1 };
		data.tangent = { 1, 0, 0 };
		data.bitangent = { 0, 1, 0 };
	}

	data.position = surfacePoint;
	//texcoords?
	return data;
}