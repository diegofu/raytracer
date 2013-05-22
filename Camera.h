#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Ray.h"
#include "ONB.h"
#include "Operations.h"
#include <math.h>
#include "Vector3.h"
#include "ONB.h"
class Camera
{
public:
	Camera() {jitter[0] = 1; jitter[1] = 1;}

	Ray getRay(double a, double b){
		if(forw.length() > 1.1 || forw.length() < 0.9){
			forw = unitVector(target - from);
		}
		
		float angleXrad = deg2rad(angleX);
		dist = resX / ( 2 * tan(angleXrad/2));
		up = unitVector(up);
		//forw.makeUnitVector();
		across = cross(forw,up);
		up = cross(-forw, across);
		across.makeUnitVector();
		at = from + (a-resX/2)*across - (b-resY/2)*up + dist*forw;
		
		Vector3 dir(unitVector(at - from));
		
		return Ray(from, dir);

	}
	Vector3 from, target, forw, up, across;
	Vector3 at;
	float angleX, angleY;
	float resX, resY;
	float dist; //distance from camera to screen
	int jitter[2];

};

#endif // _CAMERA_H_
