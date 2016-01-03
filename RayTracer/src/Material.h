#pragma once

#include <glm/glm.hpp>

#include "Texture.h"
#include "SurfacePointData.h"
#include "Light.h"

using namespace glm;

enum ShadingType {
	LAMBERTIAN, REFLECTIVE, TRANSMISSIVE_AND_REFLECTIVE, LAMBERTIAN_AND_REFLECTIVE
};

class Material
{
public:
	Material(const vec3 &color, const ShadingType shadingType);
	Material(const Texture *albedo, const ShadingType shadingType);
	Material(const vec3 &color, const Texture *albedo, const ShadingType shadingType);
	Material(const vec3 &color, const Texture *albedo, const ShadingType shadingType, const float reflectionFactor);
	Material(const vec3 &color, const Texture *albedo, const vec2 &textureScale, const ShadingType shadingType, const float reflectionFactor, const float indexOfRefraction);
	~Material();

	const vec3 getAlbedoAtPoint(const float s, const float t) const;
	const vec3 getNormalFromNormalMap(const float s, const float t) const;
	const vec3 getWorldSpaceNormal(const SurfacePointData &surfacePointData) const;

	const ShadingType shadingType;

	float reflectionFactor;
	float indexOfRefraction;

	vec2 textureScale;
	Texture *normalMap;

private:
	const vec3 color;
	const Texture *albedoTexture;

};

