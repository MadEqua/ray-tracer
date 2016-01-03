#include "RayTracer.h"

#include "Utils.h"
#include "Material.h"

#include <glm/glm.hpp>
#include <cmath>
#include <EasyBMP.h>

RayTracer::RayTracer(const Scene &scene, const RenderOptions &renderOptions) : renderOptions(renderOptions), scene(scene) {
}

void RayTracer::render() const {
	BMP output;
	output.SetSize(renderOptions.width, renderOptions.height);
	output.SetBitDepth(24);

	for (int x = 0; x < renderOptions.width; ++x) {
		for (int y = 0; y < renderOptions.height; ++y) {
			Ray r = generatePrimaryRay(x, y);
			vec3 color = castRay(r, 0);
			RGBApixel pixel{ (unsigned char)Utils::clamp(255.0f * color.b, 0.0f, 255.0f),
				(unsigned char)Utils::clamp(255.0f * color.g, 0.0f, 255.0f),
				(unsigned char)Utils::clamp(255.0f * color.r, 0.0f, 255.0f),
				255 };

			output.SetPixel(x, y, pixel);
		}
	}
	output.WriteToFile(renderOptions.outputName.c_str());
}

const Ray RayTracer::generatePrimaryRay(const int x, const int y) const {
	vec3 origin(0.0f, 0.0f, 0.0f);
	vec3 dir = rasterSpaceToWorldSpace(x, y) - origin;
	return Ray(origin, dir);
}

const vec3 RayTracer::rasterSpaceToWorldSpace(const int x, const int y) const {
	float imageAspectRatio = (float)renderOptions.width / (float)renderOptions.height; // assuming width > height
	float halfY = (float)tan(Utils::degToRad(renderOptions.fov / 2.0f));
	float px = (2 * ((x + 0.5f) / renderOptions.width) - 1) * halfY * imageAspectRatio;
	float py = (1 - 2 * ((y + 0.5f) / renderOptions.height)) * halfY;

	//TODO: camera matrix stuff

	return vec3(px, py, -1);
}

const vec3 RayTracer::castRay(const Ray &ray, const int depth) const {
	if (depth > renderOptions.maxRecursionDepth)
		return vec3(0, 0, 0);
	
	const Intersection &intersection = findNearestObjectIntersection(ray);

	if (intersection.isIntersecting()) {
		const SurfacePointData &surfacePointData = intersection.object->getSurfacePointData(intersection);
		const Material &material = intersection.object->getMaterial();

		return shade(ray, material, surfacePointData, depth);
	}
	else
		return scene.backgroundColor;
}

const Intersection RayTracer::findNearestObjectIntersection(const Ray &ray) const {
	auto objects = scene.getObjects();

	Intersection nearestIntersection;

	for (auto it = objects.begin(); it != objects.end(); ++it) {
		const Intersection &intersection = (*it)->intersect(ray);

		if (intersection.isIntersecting() && 
			(!nearestIntersection.isIntersecting() || intersection.rayT < nearestIntersection.rayT)) {
			nearestIntersection = intersection;
		}
	}
	return nearestIntersection;
}

//Note: NOT USED
const Intersection RayTracer::findAnyObjectIntersection(const Ray &ray) const {
	Intersection intersection;
	auto objects = scene.getObjects();
	for (auto it = objects.begin(); it != objects.end(); ++it) {
		intersection = (*it)->intersect(ray);
		if (intersection.isIntersecting())
			break;
	}
	return intersection;
}

const vec3 RayTracer::shade(const Ray &castedRay, const Material &material, const SurfacePointData &surfacePointData, const int depth) const {
	const vec3 &albedo = material.getAlbedoAtPoint(surfacePointData.textureCoordinates.s, surfacePointData.textureCoordinates.t);
	
	if (material.shadingType == LAMBERTIAN) {
		return shadeLambertian(castedRay, material, surfacePointData, depth);
	}
	else if (material.shadingType == REFLECTIVE) {
		return material.reflectionFactor * shadeReflective(castedRay, material, surfacePointData, depth);
	}
	else if (material.shadingType == TRANSMISSIVE_AND_REFLECTIVE) {
		vec3 refractionColor = vec3(0);
		vec3 reflectionColor = vec3(0);

		const vec3 &normal = material.getWorldSpaceNormal(surfacePointData);

		const float reflectionFactor = fresnel(castedRay.dir, normal, material.indexOfRefraction);
		// compute refraction if it is not a case of total internal reflection
		if (reflectionFactor < 1.0f)
			refractionColor = shadeTransmissive(castedRay, material, surfacePointData, depth);
		reflectionColor = shadeReflective(castedRay, material, surfacePointData, depth);
		return reflectionColor * reflectionFactor + refractionColor * (1.0f - reflectionFactor);
	}
	else if (material.shadingType == LAMBERTIAN_AND_REFLECTIVE) {
		vec3 reflectionColor = shadeReflective(castedRay, material, surfacePointData, depth);
		vec3 lambertianColor = shadeLambertian(castedRay, material, surfacePointData, depth);
		return material.reflectionFactor * reflectionColor + (1.0f - material.reflectionFactor) * lambertianColor;
	}
}

const vec3 RayTracer::shadeLambertian(const Ray &castedRay, const Material &material, const SurfacePointData &surfacePointData, const int depth) const {
	vec3 color(0);

	const vec3 &albedo = material.getAlbedoAtPoint(surfacePointData.textureCoordinates.s, surfacePointData.textureCoordinates.t);

	color = scene.ambientLight * albedo;

	const vec3 normal = material.getWorldSpaceNormal(surfacePointData);

	const auto &lights = scene.getLights();
	for (auto it = lights.begin(); it != lights.end(); ++it) {
		const vec3 lightVector = (*it)->getLightVector(surfacePointData.position);
		const Ray shadowRay(surfacePointData.position + (renderOptions.shadowBias * surfacePointData.normal), lightVector);
		const Intersection &shadowRayIntersection = findNearestObjectIntersection(shadowRay);

		if (!shadowRayIntersection.isIntersecting() || shadowRayIntersection.rayT > (*it)->distanceToPoint(shadowRay.orig)) {
			color += (*it)->getColorAndIntensity(surfacePointData.position) *
				glm::max(0.0f, dot(normal, lightVector)) *
				albedo / Utils::PI;
		}
		else if (shadowRayIntersection.object->getMaterial().shadingType == TRANSMISSIVE_AND_REFLECTIVE) {
			SurfacePointData shadowObjectSurfacePoint = shadowRayIntersection.object->getSurfacePointData(shadowRayIntersection);
			color += (*it)->getColorAndIntensity(surfacePointData.position) *
				glm::max(0.0f, dot(normal, lightVector)) *
				albedo / Utils::PI *
				0.9f * shadowRayIntersection.object->getMaterial().getAlbedoAtPoint(shadowObjectSurfacePoint.textureCoordinates.s, shadowObjectSurfacePoint.textureCoordinates.t);
		}
	}
	return color;
}

const vec3 RayTracer::shadeReflective(const Ray &castedRay, const Material &material, const SurfacePointData &surfacePointData, const int depth) const {
	const vec3 &normal = material.getWorldSpaceNormal(surfacePointData);	
	const vec3 &albedo = material.getAlbedoAtPoint(surfacePointData.textureCoordinates.s, surfacePointData.textureCoordinates.t);
	const bool outside = dot(castedRay.dir, normal) < 0;
	const vec3 bias = renderOptions.shadowBias * normal;
	const vec3 &reflectionDirection = reflect(castedRay.dir, normal);
	const vec3 reflectionRayOrig = outside ? surfacePointData.position + bias : surfacePointData.position - bias;
	const Ray reflectionRay(reflectionRayOrig, reflectionDirection);
	return castRay(reflectionRay, depth + 1) * albedo;
}

const vec3 RayTracer::shadeTransmissive(const Ray &castedRay, const Material &material, const SurfacePointData &surfacePointData, const int depth) const {
	const vec3 &normal = material.getWorldSpaceNormal(surfacePointData);
	const vec3 &albedo = material.getAlbedoAtPoint(surfacePointData.textureCoordinates.s, surfacePointData.textureCoordinates.t);
	const bool outside = dot(castedRay.dir, normal) < 0;
	const vec3 bias = renderOptions.shadowBias * normal;
	const vec3 &refractionDirection = refract(castedRay.dir, normal, material.indexOfRefraction);
	const vec3 refractionRayOrig = outside ? surfacePointData.position - bias : surfacePointData.position + bias;
	const Ray refractionRay(refractionRayOrig, refractionDirection);
	return castRay(refractionRay, depth + 1) * albedo;
}

float RayTracer::fresnel(const vec3 &I, const vec3 &N, const float refractionIndex) const {
	float cosi = Utils::clamp(dot(I, N), -1.0f, 1.0f);
	float etai = 1, etat = refractionIndex;
	if (cosi > 0) 
		std::swap(etai, etat);

	//Snell's law
	float sint = etai / etat * sqrtf(std::max(0.0f, 1.0f - cosi * cosi));

	// Total internal reflection
	if (sint >= 1) {
		return 1.0f;
	}
	else {
		float cost = sqrtf(std::max(0.0f, 1.0f - sint * sint));
		cosi = fabsf(cosi);
		float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		return (Rs * Rs + Rp * Rp) / 2.0f;
	}
}

const vec3 RayTracer::refract(const vec3 &I, const vec3 &N, const float refractionIndex) const {
	float cosi = Utils::clamp(dot(I, N), -1.0f, 1.0f);
	float etai = 1, etat = refractionIndex;
	vec3 n = N;
	if (cosi < 0.0f)
		cosi = -cosi;
	else {
		std::swap(etai, etat);
		n = -N;
	}
	float eta = etai / etat;
	float k = 1.0f - eta * eta * (1 - cosi * cosi);

	//k < 0 = total internal reflection
	return k < 0.0f ? vec3(0.0f) : (eta * I) + (eta * cosi - sqrtf(k)) * n;
}