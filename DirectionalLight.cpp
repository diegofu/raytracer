#include "DirectionalLight.h"

rgb DirectionalLight::getSpecular(const Vector3& camera, HitRecord& hit) const {
	Vector3 dir = location - hit.location;
	dir.makeUnitVector();
	hit.mat.normal = hit.mat.getNormal(hit.uv[0], hit.uv[1]);
	Vector3 norm = hit.mat.normal;
	Vector3 ref = 2 * (dot(dir, norm)) * norm - dir;

	Vector3 rayDir = camera - hit.location;
	rayDir.makeUnitVector();

	rgb color = light;
	double x = dot(rayDir, ref);
	x = pow(x, hit.mat.n_s);
	color *= x;
	color.clamp();

	Vector3 temp(hit.mat.color.r(), hit.mat.color.g(), hit.mat.color.b());
	return hit.mat.ks * color * temp.length();
}

rgb DirectionalLight::getDiffuse(const Vector3& camera, HitRecord& hit) const {
	Vector3 dir = location - hit.location;
	dir = unitVector(dir);
	rgb color = light;
	hit.mat.normal = hit.mat.getNormal(hit.uv[0], hit.uv[1]);
	double x = dot(dir, hit.mat.normal);
	if (x > 0)
		color *= x;
	else
		color *= 0;

	return color * hit.mat.getColor(hit.uv[0], hit.uv[1]) * hit.mat.kd;

}

double DirectionalLight::getShadow(const Vector3& ray, HitRecord& hit, vector<
		Shape*> shapes) const {
	//determine 
	Vector3 dir = location - hit.location; //ray from light to hit point
	double distToLight = dir.length();
	dir.makeUnitVector();
	Ray r(hit.location, dir);

	for (unsigned int i = 0; i < shapes.size(); i++) {
		if (shapes[i]->shadowHit(r, 0.00001, distToLight, 0)) {
			return 0.0f;
		}
	}
	return 1.0f;
}
