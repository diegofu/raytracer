#ifndef _RAYTRACE_
#define _RAYTRACE_

#include <vector>
#include <iostream>
#include "Vector3.h"
#include "rgb.h"
#include "Image.h"
#include "Shape.h"
#include "Triangle.h"
#include "FileParser.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "RandomNumberGenerator.h"
class Raytrace{
public: 
	Raytrace(){};
	Raytrace(char* filename);
	rgb getColor(const Ray& ray, HitRecord &hit, double ref, int depth);
	FileParser f;
	Camera camera;
	rgb background;
	rgb ambientlight;
	vector<Shape*> shapes;
	vector<Light*> lights;
	int depth;
private:
	int recurse;
	

};

#endif
