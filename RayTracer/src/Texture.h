#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using namespace glm;

class Texture
{
public:
	Texture();
	~Texture();

	virtual const vec3 getTexel(float s, float t, const vec2 &scale = vec2(1, 1)) const = 0;
};

