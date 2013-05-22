#include "rgb.h"
#include "Vector3.h"
#include "Shape.h"
#include "rgb.h"
#include "Light.h"
#include <math.h>
class Pointlight:public Light{
public:
	Pointlight();
	rgb getDiffuse(const Vector3& camera, HitRecord& hit)const;
	rgb getSpecular(const Vector3& camera, HitRecord& hit)const;
	double getShadow(const Vector3& ray, HitRecord& hit, vector<Shape*> shapes)const;
	Vector3 location;
	rgb light;

};