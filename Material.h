#ifndef _MATERIAL_
#define _MATERIAL_

#include "rgb.h"
#include "ImageTexture.h"
#include "Vector3.h"
#include "BumpMapping.h"
class ImageTexture;
class Material {

public:

	Material() {
		isTexed = false;
		bumpMap = false;
	};
	~Material() {};
	
	rgb color;
	double ka,kd,ks;
	double n_s;
	double t;

	double shadow;
	//1 means no refraction, the bigger the value
	double refract;
	ImageTexture *tex;
	bool isTexed;
	bool bumpMap;
	Vector3 normal;
	rgb getColor(double u,double v);
	Vector3 getNormal(double u, double v);
};

#endif
