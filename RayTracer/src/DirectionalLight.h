#pragma once

#include "Light.h"

#include <glm/vec3.hpp>

using namespace glm;

class DirectionalLight : public Light
{
public:
	DirectionalLight(const vec3 &direction, const float intensity, const vec3 &color);
	~DirectionalLight();

	const vec3 getLightVector(const vec3 &point) const;
	const vec3 getColorAndIntensity(const vec3 &point) const;
	float distanceToPoint(const vec3 &point) const;

private:
	const vec3 direction;
};

