#include "Intersection.h"

Intersection::Intersection(const Ray *ray, const Object *object, const float rayT) : ray(ray), object(object), rayT(rayT) {
}

Intersection::Intersection() : ray(0), object(0), rayT(-1) {
}