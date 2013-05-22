#ifndef _SHAPE_H_
#define _SHAPE_H_ 1

#include "Ray.h"
#include "Vector3.h"
#include "rgb.h"
#include "Material.h"
#include "ImageTexture.h"
class Ray;
class rgb;
class ImageTexture;

struct HitRecord
{
   float t;
   Vector3 normal;
   Material mat;
   Vector3 location;	//hit location
   double uv[2];
};

class Shape
{
public:
   virtual bool hit(const Ray& r, float tmin, float tmax, float time,
 HitRecord& record) const=0;
   virtual bool shadowHit(const Ray& r, float tmin, float tmax,
 float time) const=0;

};

#endif // _SHAPE_H_
