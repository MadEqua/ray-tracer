#include "Ray.h"

Ray::Ray() : orig(0), dir(0, 0, -1) {
}

Ray::Ray(const vec3 &o, const vec3 &d) : orig(o), dir(normalize(d)) {
}