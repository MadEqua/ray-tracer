#include "Utils.h"
#include <limits>
#include <cmath>

const float Utils::MAX_FLOAT = numeric_limits<float>::max();
const float Utils::MIN_FLOAT = numeric_limits<float>::min();
const float Utils::PI = 3.1415926535897f;
const float Utils::EPSILON_FLOAT = 1e-6f;

bool Utils::solveQuadratic(const float a, const float b, const float c, float &r0, float &r1)
{
	float discr = b * b - 4 * a * c;
	if (discr < 0)
		return false;
	else if (discr == 0)
		r0 = r1 = -0.5f * b / a;
	else {
		float q = (b > 0) ?
			-0.5f * (b + sqrt(discr)) :
			-0.5f * (b - sqrt(discr));
		r0 = q / a;
		r1 = c / q;
	}
	if (r0 > r1)
		swap(r0, r1);
	return true;
}