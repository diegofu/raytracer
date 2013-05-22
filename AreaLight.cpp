#include "AreaLight.h"
#define sampleSize 4

rgb AreaLight::getSpecular(const Vector3& camera, HitRecord& hit) const {

	Vector3 dir = location - hit.location;
	float dist = dir.length();
	dir.makeUnitVector();

	hit.mat.normal = hit.mat.getNormal(hit.uv[0], hit.uv[1]);
	Vector3 norm = unitVector(hit.mat.normal);
	Vector3 ref = 2 * (dot(dir, norm)) * norm - dir;

	Vector3 rayDir = camera - hit.location;
	rayDir.makeUnitVector();

	rgb color = lightColor / (pow(dist, 2));
	double x = dot(rayDir, ref);
	/*if( x>0) {
	 x = pow(x,hit.mat.n_s);
	 }
	 else x=0;*/
	x = pow(x, hit.mat.n_s);
	color *= x;
	color.clamp();

	Vector3 temp(hit.mat.color.r(), hit.mat.color.g(), hit.mat.color.b());
	return hit.mat.ks * color * temp.length();
}
rgb AreaLight::getDiffuse(const Vector3& camera, HitRecord& hit) const {
	Vector3 dir = location - hit.location;
	double dist = dir.length();
	dir = unitVector(dir);
	rgb color = lightColor / (pow(dist, 2));
	hit.mat.normal = hit.mat.getNormal(hit.uv[0], hit.uv[1]);

	double x = dot(dir, unitVector(hit.mat.normal));
	if (x > 0)
		color *= x;
	else
		color *= 0;

	return color * hit.mat.getColor(hit.uv[0], hit.uv[1]) * hit.mat.kd;
}

//returns ratio of number of hits/ samplesize
double AreaLight::getShadow(const Vector3& ray, HitRecord& hit,
		vector<Shape*> shapes) const {
	int intersectCount = 0;
	bool isHit = false;
	double distance = 0;
	RNG rng;
	Vector3 loc;
	for (int i = 0; i < sampleSize; i++) {
		for (int j = 0; j < sampleSize; j++) {

			isHit = false;
			//intersectCount = 0;
			loc.setX(location.x() + rng() * radius);
			loc.setY(location.y() + rng() * radius);
			loc.setZ(location.z() + rng() * radius);
			Vector3 dir = loc - hit.location;
			double distToLight = dir.length();
			dir.makeUnitVector();
			Ray r(hit.location, dir);

			for (unsigned int k = 0; k < shapes.size(); k++) {
				if (shapes[k]->shadowHit(r, 0.00001, distToLight, 0)) {
					isHit = true;
					break;		//one we hit something, we can stop checking
				}
			}
			if (isHit) {
				intersectCount++;
			}
		}
	}
	return (double(sampleSize * sampleSize) - intersectCount) / (double(sampleSize
			* sampleSize));
}
