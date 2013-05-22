#ifndef _LIGHT_
#define _LIGHT_
#include "rgb.h"
#include "Shape.h"
#include <vector>
class Light{

public:
	Light(){};
	virtual rgb getDiffuse(const Vector3& camera, HitRecord& hit)const = 0;
	virtual rgb getSpecular(const Vector3& camera, HitRecord &hit)const = 0;
	virtual double getShadow(const Vector3& ray, HitRecord& hit, vector<Shape*> shapes)const =0;
};

#endif