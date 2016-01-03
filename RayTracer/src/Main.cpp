#include <iostream>

#include "Scene.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "TriangleMesh.h"
#include "AABox.h"
#include "RayTracer.h"
#include "Material.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "CheckerBoardTexture.h"
#include "FileTexture.h"

using namespace std;

int main() {
	Scene scene(vec3(0.1f), vec3(0, 191.0f / 255.0f, 1));

	vec3 lightBlue(190./255., 237./255., 1.);
	vec3 lightRed(248. / 255., 192./ 255., 196./255);

	//FileTexture bricksNormalMap("textures/bricksNormal.jpg");
	//FileTexture brickTexture("textures/bricksAlbedo.jpg");
	//FileTexture masonryNormalMap("textures/masonryNormal.jpg");
	//FileTexture masonryTexture("textures/masonryAlbedo.jpg");

	FileTexture normalMap2("textures/normal4.jpg");

	CheckerBoardTexture brownCheckerBoardTexture(vec3(1), vec3(160. / 255., 82. / 255., 45. / 255.));

	Material brownCheckerBoardMaterial(vec3(1), &brownCheckerBoardTexture, vec2(0.2f), LAMBERTIAN, 0.8f, 1.5f);
	//brownCheckerBoardMaterial.normalMap = &normalMap2;

	Material whiteMaterial(vec3(1), 0, vec2(0.1f), LAMBERTIAN, 0.8f, 1.5f);

	//Material brickMaterial(vec3(1), &brickTexture, vec2(0.02f), LAMBERTIAN, 0.8f, 1.5f);
	//brickMaterial.normalMap = &bricksNormalMap;

	//Material whiteRoughMaterial(vec3(1), 0, vec2(0.2f), LAMBERTIAN, 0.8f, 1.5f);
	//whiteRoughMaterial.normalMap = &normalMap;

	Material redMaterial(vec3(1, 0, 0), 0, vec2(0.05f), LAMBERTIAN, 0.8f, 1.5f);
	//redMaterial.normalMap = &normalMap2;

	Material greenMaterial(vec3(0, 1, 0), 0, vec2(0.05f), LAMBERTIAN, 0.8f, 1.5f);
	//greenMaterial.normalMap = &normalMap2;

	Material blueGlassMaterial(lightBlue, 0, vec2(1.0f), TRANSMISSIVE_AND_REFLECTIVE, 0.95f, 1.5f);
	blueGlassMaterial.normalMap = &normalMap2;

	//Material masonryMaterial(vec3(1), &masonryTexture, vec2(0.1f), LAMBERTIAN, 0.8f, 1.5f);
	//masonryMaterial.normalMap = &masonryNormalMap;

	Material mirrorMaterial(vec3(1), 0, vec2(1.0f), REFLECTIVE, 0.8f, 1.5f);
	mirrorMaterial.normalMap = &normalMap2;

	//Material glossyMaterial(lightRed, 0, vec2(1.0f), LAMBERTIAN_AND_REFLECTIVE, 0.4f, 1.5f);
	//glossyMaterial.normalMap = &normalMap2;

	scene.addObject(new Plane(vec3(-10.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f), redMaterial));
	scene.addObject(new Plane(vec3(10.0f, 0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f), greenMaterial));
	scene.addObject(new Plane(vec3(0.0f, -5.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), brownCheckerBoardMaterial));
	scene.addObject(new Plane(vec3(0.0f, 0.0f, -35.0f), vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), whiteMaterial));
	scene.addObject(new Plane(vec3(0.0f, 13.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), whiteMaterial));
	scene.addObject(new Plane(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 0.0f, 0.0f), whiteMaterial));

	scene.addObject(new Sphere(vec3(3.0f, -1.0f, -25.0f), 4.0f, mirrorMaterial));
	scene.addObject(new Sphere(vec3(-4.0f, -3.0f, -15.0f), 2.0f, mirrorMaterial));
	scene.addObject(new Sphere(vec3(5.0f, -4.0f, -13.0f), 1.0f, mirrorMaterial));
	//scene.addObject(new Sphere(vec3(-1.5f, -4.3f, -21.0f), 0.7f, whiteMaterial));
	
	//scene.addObject(new AABox(vec3(-0.0f, 9.0f, -30.0f), vec3(21.0f, 2.0f, 3.0f), blueGlassMaterial));

	//LIGHTS
	scene.addLight(new PointLight(vec3(0.0f, 7.0f, -18.0f), 650.0f, vec3(1.0f, 1.0f, 1.0f)));
	//scene.addLight(new DirectionalLight(vec3(0.0f, 0.0f, -1.0f), 1.0f, vec3(1.0f, 1.0f, 1.0f)));

	//MESH TEST
	/*TriangleMesh *mesh = new TriangleMesh("meshes/bunny.obj", blueGlassMaterial);
	mesh->setPosition(1, -7.1f, -18);
	mesh->setRotation(0.0f, 0.0f, 0.0f);
	mesh->setScale(50, 50, 50);
	mesh->applyTransforms();
	scene.addObject(mesh);*/
	
	//REFRACTION TEST
	/*scene.addObject(new Plane(vec3(0.0f, 0.0f, -35.0f), vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), Material(vec3(1, 1, 1), new CheckerBoardTexture(vec2(0.1f, 0.1f), vec3(1), vec3(0)), LAMBERTIAN)));
	scene.addObject(new AABox(vec3(0.0f, 0.0f, -33.0f), vec3(2.0f, 25.0f, 2.0f), Material(vec3(0.5f, 0.3f, 1.0f), 0, LAMBERTIAN, 0.8f, 1.5f)));
	scene.addObject(new Sphere(vec3(3.0, 0, -20), 5.5f, Material(vec3(1.0f, 1.0f, 1.0f), 0, TRANSMISSIVE_AND_REFLECTIVE, 0.8f, 1.5f)));
	scene.addLight(new PointLight(vec3(0.0f, 3.0f, -5.0f), 2500.0f, vec3(1.0f, 1.0f, 1.0f)));*/

	RenderOptions renderOptions;
	renderOptions.fov = 51.52f;
	renderOptions.width = 800;
	renderOptions.height = 800;
	renderOptions.maxRecursionDepth = 8;
	renderOptions.shadowBias = 0.001f;
	renderOptions.outputName = "render.bmp";

	RayTracer rayTracer(scene, renderOptions);
	rayTracer.render();

	return 0;
}