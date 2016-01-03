#include "DirectionalLight.h"

#include <glm/glm.hpp>
#include "Utils.h"

using namespace glm;


DirectionalLight::DirectionalLight(const vec3 &direction, const float intensity, const vec3 &color) : direction(normalize(direction)), Light(intensity, color)
{
}


DirectionalLight::~DirectionalLight()
{
}

const vec3 DirectionalLight::getLightVector(const vec3 &point) const {
	return -direction;
}

const vec3 DirectionalLight::getColorAndIntensity(const vec3 &point) const {
	return color * intensity;
}

float DirectionalLight::distanceToPoint(const vec3 &point) const {
	return Utils::MAX_FLOAT;
}