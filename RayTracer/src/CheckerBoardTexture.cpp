#include "CheckerBoardTexture.h"

CheckerBoardTexture::CheckerBoardTexture(const vec3 &color1, const vec3 &color2) : color1(color1), color2(color2)
{
}

CheckerBoardTexture::~CheckerBoardTexture()
{
}

const vec3 CheckerBoardTexture::getTexel(float s, float t, const vec2 &scale) const {
	return ((modulo(s * scale.s) < 0.5f) ^ (modulo(t * scale.t) < 0.5f)) == 0 ? color1 : color2;
}