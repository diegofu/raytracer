#ifndef _DIRECTION_LIGHT
#define _DIRECTION_LIGHT


#include "Light.h"
#include "rgb.h"
#include "Vector3.h"
#include "Material.h"

class DirectionalLight:public Light{
public:
	DirectionalLight(){}
	rgb getDiffuse(const Vector3& camera, HitRecord& hit)const;
	rgb getSpecular(const Vector3& camera, HitRecord& hit)const;
	double getShadow(const Vector3& ray, HitRecord& hit, vector<Shape*> shapes)const;
	Vector3 location;
	rgb light;

};

#endif