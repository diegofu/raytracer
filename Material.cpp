#include "Material.h"

rgb Material::getColor(double u,double v){
		if(!isTexed) return color;
		return tex->getColor(u,v);
};

Vector3 Material::getNormal(double u, double v){
	if(!bumpMap) return normal;
	return tex->getNormal(u,v);
	//return Vector3(0,0,0);
}
