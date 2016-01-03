#pragma once

#include <string>
#include <glm/vec3.hpp>

using namespace std;
using namespace glm;

struct RenderOptions {
	int width;
	int height;
	float fov;
	int maxRecursionDepth;
	string outputName;
	float shadowBias;
};