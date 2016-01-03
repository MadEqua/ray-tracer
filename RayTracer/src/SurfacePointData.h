#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using namespace glm;

//All world space except texture coordinates
struct SurfacePointData {
	vec3 normal;
	vec2 textureCoordinates;
	vec3 position;

	//Extra stuff
	vec3 tangent;
	vec3 bitangent;
};