#include "PointLight.h"

#include <glm/glm.hpp>
#include "Utils.h"

using namespace glm;

PointLight::PointLight(const vec3 &position, const float intensity, const vec3 &color, const vec3 &attenuationFactors) :
position(position), Light(intensity, color), a(attenuationFactors.x), b(attenuationFactors.y), c(attenuationFactors.z)
{
}


PointLight::~PointLight()
{
}

const vec3 PointLight::getLightVector(const vec3 &point) const {
	return normalize(position - point);
}

const vec3 PointLight::getColorAndIntensity(const vec3 &point) const {
	float dist = glm::distance(position, point);
	//vec3 dist = position - point;
	//float sqDist = dist.x * dist.x + dist.y * dist.y + dist.z * dist.z;
	return (color * intensity) / (a + (b * dist) + (c * dist * dist));

	//return (color * intensity) / (4.0f * Utils::PI * sqDist);
}

float PointLight::distanceToPoint(const vec3 &point) const {
	return glm::distance(position, point);
}