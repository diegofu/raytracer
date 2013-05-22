/*
 * BumpMapping.cpp
 *
 *  Created on: 2010-11-27
 *      Author: diego
 */

#include "BumpMapping.h"

BumpMapping::BumpMapping(string filename, string filename2) :
	ImageTexture(filename) {
	normalImage = new Image();
	normalImage->readPPM(filename2);
	mapped = true;

}
Vector3 BumpMapping::getNormal(double _u, double _v) {
	double u = _u - int(_u);
	double v = _v - int(_v);
	u *= (normalImage->getWidth() - 3);
	v *= (normalImage->getHeight() - 3);
	int iu = ((int) u);
	int iv = ((int) v);
	//cout<<"u: "<<iu<<" v: "<<iv<<endl;
//	const double x = _color.r();
//	const double y = _color.g();
//	const double z = _color.b();
	rgb _color = normalImage->color(iu, iv);
	return (Vector3(_color.r()*2 - 1, _color.g()*2 - 1, _color.b()*2 - 1));

}
