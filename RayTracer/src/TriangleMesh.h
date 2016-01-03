#pragma once

#include "Object.h"

#include "Intersection.h"
#include "SurfacePointData.h"

#include "AABox.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>

#include <string>
#include <iostream>

using namespace glm;
using namespace std;

class TriangleMesh : public Object
{
public:
	TriangleMesh(const string path, const Material &material);
	~TriangleMesh();

	const Intersection intersect(const Ray &ray) const;
	const SurfacePointData getSurfacePointData(const Intersection &intersection) const;

	inline void setPosition(const float x, const float y, const float z) { position.x = x; position.y = y; position.z = z; }
	inline void setRotation(const float angleX, const float angleY, const float angleZ) { rotation.x = angleX; rotation.y = angleY; rotation.z = angleZ; }
	inline void setScale(const float x, const float y, const float z) { scale.x = x; scale.y = y; scale.z = z; }
	void applyTransforms();

	inline const mat4& getModelMatrix() const { return modelMatrix; }
	inline const mat4& getNormalMatrix() const { return normalMatrix; }

private:
	Assimp::Importer *importer;
	const AABox *boundingBox;

	vec3 scale;
	vec3 rotation;

	mat4 modelMatrix; //Object to world Matrix
	mat4 normalMatrix; //Tranposed Inverse Model Matrix

	inline void computeNormalMatrix() { normalMatrix = transpose(inverse(modelMatrix)); };

	const Intersection intersectTriangle(const Ray &ray, const vec3 &a, const vec3 &b, const vec3 &c) const;
	const void computeBounds(const aiVector3D &vertex, vec3 &min, vec3 &max) const;
};

