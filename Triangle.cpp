#include "Triangle.h"

Triangle::Triangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2,
		const rgb& _color) :
	p0(_p0), p1(_p1), p2(_p2), color(_color) {

}

Triangle::Triangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2,
		const Material& _mat,const Vector3& _vt0,const Vector3& _vt1,const Vector3& _vt2) :p0(_p0), p1(_p1), p2(_p2), mat(_mat) , vt0(_vt0), vt1(_vt1), vt2(_vt2){

}

bool Triangle::hit(const Ray& r, float tmin, float tmax, float time,
		HitRecord& record) const {

	float tval;
	float A = p0.x() - p1.x();
	float B = p0.y() - p1.y();
	float C = p0.z() - p1.z();

	float D = p0.x() - p2.x();
	float E = p0.y() - p2.y();
	float F = p0.z() - p2.z();

	float G = r.direction().x();
	float H = r.direction().y();
	float I = r.direction().z();

	float J = p0.x() - r.origin().x();
	float K = p0.y() - r.origin().y();
	float L = p0.z() - r.origin().z();

	float EIHF = E * I - H * F;
	float GFDI = G * F - D * I;
	float DHEG = D * H - E * G;

	float denom = (A * EIHF + B * GFDI + C * DHEG);

	float beta = (J * EIHF + K * GFDI + L * DHEG) / denom;

	if (beta <= 0.0f || beta >= 1.0f)
		return false;

	float AKJB = A * K - J * B;
	float JCAL = J * C - A * L;
	float BLKC = B * L - K * C;

	float gamma = (I * AKJB + H * JCAL + G * BLKC) / denom;
	if (gamma <= 0.0f || beta + gamma >= 1.0f)
		return false;

	tval = -(F * AKJB + E * JCAL + D * BLKC) / denom;
	if (tval >= tmin && tval <= tmax) {

		record.t = tval;
		record.mat = mat;
		record.mat.normal = unitVector(cross((p1 - p0), (p2 - p0)));
		record.location = r.pointAtParameter(tval);

		//calculating uv

		double uvs[3][2];

		uvs[0][0] = vt0.x();
		uvs[1][0] = vt1.x();
		uvs[2][0] = vt2.x();

		uvs[0][1] = vt0.y();
		uvs[1][1] = vt1.y();
		uvs[2][1] = vt2.y();

		float alpha = 1 - beta - gamma;
		record.uv[0] = alpha * uvs[0][0] + beta * uvs[1][0] + gamma * uvs[2][0];
		record.uv[1] = alpha * uvs[0][1] + beta * uvs[1][1] + gamma * uvs[2][1];
		return true;
	}

	return false;
}

bool Triangle::shadowHit(const Ray& r, float tmin, float tmax, float time) const {
	float tval;
	float A = p0.x() - p1.x();
	float B = p0.y() - p1.y();
	float C = p0.z() - p1.z();

	float D = p0.x() - p2.x();
	float E = p0.y() - p2.y();
	float F = p0.z() - p2.z();

	float G = r.direction().x();
	float H = r.direction().y();
	float I = r.direction().z();

	float J = p0.x() - r.origin().x();
	float K = p0.y() - r.origin().y();
	float L = p0.z() - r.origin().z();

	float EIHF = E * I - H * F;
	float GFDI = G * F - D * I;
	float DHEG = D * H - E * G;

	float denom = (A * EIHF + B * GFDI + C * DHEG);

	float beta = (J * EIHF + K * GFDI + L * DHEG) / denom;

	if (beta <= 0.0f || beta >= 1.0f)
		return false;

	float AKJB = A * K - J * B;
	float JCAL = J * C - A * L;
	float BLKC = B * L - K * C;

	float gamma = (I * AKJB + H * JCAL + G * BLKC) / denom;
	if (gamma <= 0.0f || beta + gamma >= 1.0f)
		return false;

	tval = -(F * AKJB + E * JCAL + D * BLKC) / denom;

	return (tval >= tmin && tval <= tmax);
}

