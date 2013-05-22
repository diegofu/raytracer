#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_ 1

#include "Shape.h"
#include "Vector3.h"
#include "rgb.h"
#include "Ray.h"
#include "Material.h"
#include "ImageTexture.h"
#include "Operations.h"
#include "BumpMapping.h"
class Triangle : public Shape
{
public:
	Triangle(const Vector3& _p0, const Vector3& _p1,
		const Vector3& _p2, const rgb& _color);
	Triangle(const Vector3& _p0, const Vector3& _p1,
		const Vector3& _p2, const Material& _mat,
		const Vector3& _vt0,const Vector3& _vt1,const Vector3& _vt2);
	bool hit(const Ray& r, float tmin, float tmax, float time,
		HitRecord& record) const;
	bool shadowHit(const Ray& r, float tmin, float tmax,
		float time) const;
	Vector3 p0;
	Vector3 p1;
	Vector3 p2;
	Vector3 vt0;
	Vector3 vt1;
	Vector3 vt2;
	rgb color;
	Material mat;
};

#endif // _TRIANGLE_H_

