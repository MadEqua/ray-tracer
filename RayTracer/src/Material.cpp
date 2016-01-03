#include "Material.h"

Material::Material(const vec3 &color, const ShadingType shadingType) : 
Material(color, 0, vec2(1), shadingType, 0.8f, 1.0f) {
}

Material::Material(const Texture *albedo, const ShadingType shadingType) : 
Material(vec3(1.0f), albedo, vec2(1), shadingType, 0.8f, 1.0f) {
}

Material::Material(const vec3 &color, const Texture *albedo, const ShadingType shadingType) : 
Material(color, albedo, vec2(1), shadingType, 0.8f, 1.0f) {
}

Material::Material(const vec3 &color, const Texture *albedo, const ShadingType shadingType, const float reflectionFactor) :
Material(color, albedo, vec2(1), shadingType, reflectionFactor, 1.0f) {
}

Material::Material(const vec3 &color, const Texture *albedoTexture, const vec2 &textureScale, const ShadingType shadingType, const float reflectionFactor, const float indexOfRefraction) :
color(color), albedoTexture(albedoTexture), shadingType(shadingType),
reflectionFactor(reflectionFactor), indexOfRefraction(indexOfRefraction), textureScale(textureScale), normalMap(0) {
}

Material::~Material() {
}

const vec3 Material::getAlbedoAtPoint(const float s, const float t) const {
	if (albedoTexture == 0)
		return color;
	else
		return color * albedoTexture->getTexel(s, t, textureScale);
}

const vec3 Material::getNormalFromNormalMap(const float s, const float t) const {
	return normalMap->getTexel(s, t, textureScale);
}

const vec3 Material::getWorldSpaceNormal(const SurfacePointData &surfacePointData) const {
	if (normalMap == 0)
		return surfacePointData.normal;
	else {
		vec3 normal = getNormalFromNormalMap(surfacePointData.textureCoordinates.s, surfacePointData.textureCoordinates.t);
		normal = (normal * 2.0f) - 1.0f;
		mat3 tangentToWorld(surfacePointData.tangent, surfacePointData.bitangent, surfacePointData.normal); //Column Major	
		return normalize(tangentToWorld * normal); //M * v -> correct column major multiplication order
	}
}
