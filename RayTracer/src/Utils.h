#pragma once

#include <algorithm>

using namespace std;

class Utils {
public:
	static const float MAX_FLOAT;
	static const float MIN_FLOAT;
	static const float PI;
	static const float EPSILON_FLOAT;

	static bool solveQuadratic(const float a, const float b, const float c, float &r0, float &r1);

	inline static float clamp(const float v, const float lo, const float hi) {
		return std::max(lo, std::min(hi, v));
	}

	inline static float degToRad(const float deg) {
		return (PI / 180.0f * deg);
	}

	inline static bool floatEquals(const float value, const float comp, const float epsilon = EPSILON_FLOAT) {
		return abs(value - comp) <= epsilon;
	}
};