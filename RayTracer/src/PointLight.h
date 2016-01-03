#pragma once

#include "Light.h"

#include <glm/vec3.hpp>

using namespace glm;

class PointLight : public Light
{
public:
	PointLight(const vec3 &position, const float intensity, const vec3 &color, const vec3 &attenuationFactors = vec3(0, 1, 1));
	~PointLight();

	const vec3 getLightVector(const vec3 &point) const;
	const vec3 getColorAndIntensity(const vec3 &point) const;
	float distanceToPoint(const vec3 &point) const;

private:
	const vec3 position;
	float a, b, c;
};

