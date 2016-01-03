#include "Object.h"

Object::Object(const vec3 &position, const Material &material) : material(material), position(position) {
}

Object::Object(const Material &material) : material(material) {
}