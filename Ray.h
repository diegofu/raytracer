#ifndef _RAY_H_
#define _RAY_H_ 1

#include "Vector3.h"
#include "RandomNumberGenerator.h"
#define numOfRays 16
class Ray {
public:

    Ray() {}
    Ray(const Vector3& a, const Vector3& b)
    {data[0] = a; data[1] = b;}
	Ray(const double *x, const double *y){
		data[0].setX(x[0]);
		data[0].setY(x[1]);
		data[0].setZ(x[2]);
		data[1].setX(x[0]);
		data[1].setY(x[1]);
		data[1].setZ(x[2]);

	}
    Ray(const Ray& r) {*this = r;}
    Vector3 origin() const {return data[0];}
    Vector3 direction() const {return data[1];}
    Vector3 pointAtParameter(float t) const
    { return data[0] + t*data[1]; }
    //double *sample;
	//data[0] = origin data[1] = direction
    Vector3 data[2];


};

inline ostream &operator<<(ostream &os, const Ray &r) {
   os << "(" << r.origin() << ") + t("  << r.direction() << ")";
   return os;
}
#endif // _RAY_H_
