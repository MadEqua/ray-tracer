#pragma once

#include "Scene.h"
#include "RenderOptions.h"
#include "Ray.h"
#include "Utils.h"
#include "Intersection.h"
#include <glm/vec3.hpp>

using namespace glm;

class RayTracer {
private:
	const RenderOptions &renderOptions;
	const Scene &scene;

	const vec3 rasterSpaceToWorldSpace(const int x, const int y) const;
	const Ray generatePrimaryRay(const int x, const int y) const;

	const vec3 castRay(const Ray &ray, const int depth) const; //compute the color at intersection point
	const Intersection findNearestObjectIntersection(const Ray &ray) const;
	const Intersection findAnyObjectIntersection(const Ray &ray) const;

	float fresnel(const vec3 &I, const vec3 &N, const float refractionIndex) const; //return ratio of reflected light
	const vec3 refract(const vec3 &I, const vec3 &N, const float refractionIndex) const;

	const vec3 shade(const Ray &castedRay, const Material &material, const SurfacePointData &surfacePointData, const int depth) const;

	const vec3 shadeLambertian(const Ray &castedRay, const Material &material, const SurfacePointData &surfacePointData, const int depth) const;
	const vec3 shadeReflective(const Ray &castedRay, const Material &material, const SurfacePointData &surfacePointData, const int depth) const;
	const vec3 shadeTransmissive(const Ray &castedRay, const Material &material, const SurfacePointData &surfacePointData, const int depth) const;

public:
	RayTracer(const Scene &scene, const RenderOptions &renderOptions);
	void render() const;
};