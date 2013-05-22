#ifndef _DYN_SPHERE_H_
#define _DYN_SPHERE_H_

#include "Shape.h"
#include "Vector3.h"
#include "Ray.h"
#include "rgb.h"
#include "Material.h"

class DynSphere : public Shape

{
public:
   DynSphere(const Vector3& _ocenter, float _radius,
       const Material& mat, float mintime, float maxtime);
   bool hit(const Ray& r, float tmin, float tmax, float time,
 HitRecord& record)const;
   bool shadowHit(const Ray& r, float tmin, float tmax, float time)
   const; Vector3 getCenter(float time)const;

   Vector3 ocenter;
   float mintime;
   float maxtime;
   float radius;
	Material mat;
};

#endif // _DYN_SPHERE_H__
