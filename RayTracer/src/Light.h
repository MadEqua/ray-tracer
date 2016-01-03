#pragma once

#include <glm/vec3.hpp>

using namespace glm;

class Light {
public:
	const vec3 color;
	const float intensity;
	Light(const float intensity, const vec3 &color);

	virtual const vec3 getLightVector(const vec3 &point) const = 0;
	virtual const vec3 getColorAndIntensity(const vec3 &point) const = 0;
	virtual float distanceToPoint(const vec3 &point) const = 0;
};