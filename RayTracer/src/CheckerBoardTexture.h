#pragma once

#include "Texture.h"
#include <cmath>

#include <glm/vec2.hpp>

using namespace glm;

class CheckerBoardTexture : public Texture
{
public:
	CheckerBoardTexture(const vec3 &color1, const vec3 &color2);
	~CheckerBoardTexture();

	const vec3 getTexel(float s, float t, const vec2 &scale = vec2(1, 1)) const;

private:
	vec3 color1;
	vec3 color2;

	inline float modulo(const float x) const {
		return x - std::floor(x);
	}
};