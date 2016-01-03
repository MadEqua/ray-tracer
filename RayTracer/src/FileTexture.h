#pragma once

#include <string>
#include "Texture.h"

#include "IL/il.h"

using namespace std;

class FileTexture : public Texture
{
public:
	FileTexture(const string &path);
	~FileTexture();

	const vec3 getTexel(float s, float t, const vec2 &scale = vec2(1, 1)) const;

private:
	ILint imageHandle;
	int width, height, channels;

	const vec3 bilinearInterpolation(float u, float v) const;
	const vec3 getTexelFromFile(const int x, const int y) const;
};

