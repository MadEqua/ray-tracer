#pragma once

#include <glm/glm.hpp>

using namespace glm;

class Ray
{
public:
	vec3 orig;
	vec3 dir;

	Ray();
	Ray(const vec3 &o, const vec3 &d);
};