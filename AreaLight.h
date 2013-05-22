/*
 * AreaLight.h
 *
 *  Created on: 2010-11-28
 *      Author: diego
 */

#ifndef _AREALIGHT_H_
#define _AREALIGHT_H_
#include "Light.h"
#include "Vector3.h"
#include "RandomNumberGenerator.h"
class AreaLight: public Light {
public:
	AreaLight() {
	}
	AreaLight(const Vector3& _location, double _radius, const rgb& _lightColor) :
		location(_location), radius(_radius), lightColor(_lightColor) {
	}
	rgb getDiffuse(const Vector3& camera, HitRecord& hit) const;
	rgb getSpecular(const Vector3& camera, HitRecord& hit) const;
	double
	getShadow(const Vector3& ray, HitRecord& hit, vector<Shape*> shapes) const;

	Vector3 location;
	double radius;
	rgb lightColor;
	Vector3 direction;
};

#endif /* AREALIGHT_H_ */
