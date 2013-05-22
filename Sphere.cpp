#include "Sphere.h"

Sphere::Sphere(const Vector3& _center, float _radius, const rgb& _color)
   : center(_center), radius(_radius), color(_color) {}

Sphere::Sphere(const Vector3& _center, float _radius, const Material& _mat)
	: center(_center), radius(_radius), mat(_mat){}
bool Sphere::hit(const Ray& r, float tmin, float tmax, float time,
      HitRecord& record)const
{
   Vector3 temp = r.origin() - center;

   double a = dot( r.direction(), r.direction() );
   double b = 2*dot( r.direction(), temp );
   double c = dot( temp, temp ) - radius*radius;

   double discriminant = b*b- 4*a*c;

   // first check to see if ray intersects sphere
   if ( discriminant > 0 )
   {
      discriminant = sqrt( discriminant );
      double t = (- b - discriminant) / (2*a);

      // now check for valid interval
      if (t < tmin)
         t = (- b + discriminant) / (2*a);
      if (t < tmin || t > tmax)
         return false;

      // we have a valid hit
	  

      record.t = t;
      record.mat = mat;
      Vector3 n = record.mat.normal = unitVector(r.origin() + t* r.direction()
                           - center);

	  record.location = r.pointAtParameter(t);

	  //calculate uv coordinates
	double twopi = 6.28318530718;
	Vector3 vn(0,0,1);
	Vector3 ve(0,1,0);
	double phi = acos(dot(vn,n));

	record.uv[0] = phi*2/twopi;
	double theta = acos(dot(n,ve)/sin(phi));
	if(dot(cross(vn,ve),n)>0){
		record.uv[1] = theta;
	}else{
		record.uv[1] = 1-theta;
	}
	
	/*
	  double twopi = 6.28318530718;
	  double theta = acos(n.z());
	  double phi = atan2(n.y(), n.x());
	  if(phi < 0) phi += twopi;
	  
	  double one_over_2pi = 1/twopi;
	  float one_over_pi = 2/twopi;
	  record.uv[0] = phi*one_over_2pi;
	  record.uv[1] = (twopi/2 - theta) * one_over_pi;
	*/
      return true;
   }
   return false;
}

bool Sphere::shadowHit(const Ray& r, float tmin, float tmax,
                       float time)const
{
   Vector3 temp = r.origin() - center;

   double a = dot( r.direction(), r.direction() );
   double b = 2*dot( r.direction(), temp );
   double c = dot( temp, temp ) - radius*radius;

   double discriminant = b*b- 4*a*c;

   // first check to see if ray intersects sphere
   if ( discriminant > 0 )
   {
      discriminant = sqrt( discriminant );
      double t = (- b - discriminant) / (2*a);

      // now check for valid interval
      if (t < tmin + radius)
         t = (- b + discriminant) / (2*a);
      if (t < tmin + radius|| t > tmax)
         return false;

      //we have a valid hit

      return true;
   }
   return false;
}

