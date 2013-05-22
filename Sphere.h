#ifndef _SPHERE_H_
#define _SPHERE_H_ 1

#include "Shape.h"
#include "Vector3.h"
#include "Ray.h"
#include "rgb.h"
#include "Material.h"
#include "ImageTexture.h"

class Sphere : public Shape
{
public:
   Sphere(const Vector3& _center, float radius, const rgb&_color);
   Sphere(const Vector3& _center, float radius, const Material& _mat);
   //BBox boundingBox() const;
   bool hit(const Ray& r, float tmin, float tmax, float time,
 HitRecord& record) const;
   bool shadowHit(const Ray& r, float tmin, float tmax, float time)
       const;
   rgb getNormal(double u, double v) const;
   Vector3 center;
   float radius;
   rgb color;
   Material mat;
};

#endif // _SPHERE_H__
