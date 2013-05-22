#ifndef __FILE_PARSER__
#define __FILE_PARSER__

#include <vector>
#include <iostream>
#include <fstream>
#include <istream>
#include <math.h>
#include "Shape.h"
#include "Material.h"
#include "Camera.h"
#include "rgb.h"
#include "Sphere.h"
#include "Triangle.h"
#include "mesh.h"
#include "Vector3.h"
#include "Light.h"
#include "Pointlight.h"
#include "ImageTexture.h"
#include <string>
#include <cstring>
#include "DynSphere.h"
#include "DirectionalLight.h"
#include "BumpMapping.h"
#include "AreaLight.h"
using namespace std;

class FileParser {

public:
	FileParser() {};
	char* getFileName(){
		return outfile;
	}

	Vector3 vec3Convert(Vec3 v){
		return Vector3(v.ptr[0],v.ptr[1],v.ptr[2]);

	}
	bool parse(const char* filename,Camera *camera,
		rgb *background, rgb *ambientLight, vector<Shape*> *shapes, vector<Light*> *lights);
	char outfile[25];
	int depth;
	
};

#endif
