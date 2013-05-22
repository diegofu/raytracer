#include "Raytrace.h"

Raytrace::Raytrace(char* filename) {

	if (f.parse(filename, &camera, &background, &ambientlight, &shapes, &lights)) {
		HitRecord rec;
		depth = f.depth;
		recurse = 0;
		Image im(camera.resX, camera.resY);

		rgb color(0,0,0);
		RNG rng;
		int sampleSize = camera.jitter[0] * camera.jitter[1];
		double sample[sampleSize][2];

		//generate super sampling, in this case jitter;
		for (int i = 0; i < camera.jitter[0]; i++) {
			for (int j = 0; j < camera.jitter[1]; j++) {
				double n1 = (double(i) + rng()) / camera.jitter[0];
				double n2 = (double(j) + rng()) / camera.jitter[1];
				sample[i * camera.jitter[0] + j][0] = n1;
				sample[i * camera.jitter[0] + j][1] = n2;
			}
		}

		for (int y = 0; y < camera.resY; y++) {
			for (int x = 0; x < camera.resX; x++) {
				for (int i = 0; i < sampleSize; i++) {
					Ray r = camera.getRay(x + sample[i][0], y + sample[i][1]);
					color += getColor(r, rec, 1, 0);
				}
				color /= camera.jitter[0] * camera.jitter[1];
				im.set(x, y, color);
				color = rgb(0,0,0);
			}

		}

		char *output;

		output = f.outfile;
		im.writePPM(output);

	}
}
rgb Raytrace::getColor(const Ray& ray, HitRecord &hit, double incRef,
		int rDepth) {
	if (depth == rDepth)
		return rgb(0, 0, 0);

	float tmax = 100000.0f;
	bool isHit = false;
	;

	for (unsigned int i = 0; i < shapes.size(); i++) {
		if (shapes[i]->hit(ray, 0.0001f, tmax, 0, hit)) {
			tmax = hit.t;
			isHit = true;
		}
	}
	if (!isHit)
		return background;
	rgb cAmbient = hit.mat.ka * ambientlight * hit.mat.color;
	rgb cDiffuse(0, 0, 0);
	rgb cSpecular(0, 0, 0);
	double shadowCoef;
	for (unsigned int i = 0; i < lights.size(); i++) {
		shadowCoef = lights[i]->getShadow(hit.location, hit, shapes);
		cDiffuse += lights[i]->getDiffuse(camera.from, hit) * shadowCoef;
		cSpecular += lights[i]->getSpecular(camera.from, hit) * shadowCoef;
	}

	//reflected color
	Vector3 normal = hit.mat.normal;
	if (dot(normal, ray.direction()) > 0) {
		normal = -normal;
	}
	Vector3 ref = ray.direction() - 2 * (dot(ray.direction(), normal)) * normal;
	//Vector3 ref = 2*(dot(ray.direction(),normal))*normal - ray.direction();
	Vector3 refOrig = hit.location;
	ref.makeUnitVector();
	Ray reflectedRay(refOrig, ref);
	HitRecord _hit;
	rgb reflectedColor;
	reflectedColor += getColor(reflectedRay, _hit, incRef, rDepth + 1);

	//transmitted ray
	double refIndex = hit.mat.refract;
	double transmittance = hit.mat.t;
	rgb transmittedColor;
	if (transmittance > 0) {
		Vector3 transRayDir;
		Vector3 n = normal;
		Vector3 d = unitVector(ray.direction());
		double c = 1 - pow(incRef, 2) * (1 - pow(dot(d, n), 2)) / pow(refIndex,
				2);
		if (c > 0) {
			//cout<<c<<endl;
			Vector3 s = incRef * (d - n * dot(d, n)) / refIndex;
			transRayDir = s - n * sqrt(c);
			transRayDir.makeUnitVector();
			Ray transRay(hit.location, transRayDir);
			HitRecord transHit;
			transmittedColor = getColor(transRay, transHit, refIndex, rDepth
					+ 1);
		}
		/*
		 double beta = incRef / refIndex;
		 double cosThetaIn = dot(normal,-ray.direction());
		 double sinThetaIn = sin(acos(cosThetaIn));
		 Vector3 transRayDir = (beta*cosThetaIn - pow((1-pow(beta,2)*pow(sinThetaIn,2)),.5))*normal;
		 transRayDir.makeUnitVector();
		 Ray transRay (hit.location,-transRayDir);
		 HitRecord transHit;
		 transmittedColor = getColor(transRay,transHit,refIndex,rDepth +1);
		 */
	}
	rgb c = cAmbient + cSpecular + (cDiffuse + reflectedColor * hit.mat.ks)
			* (1 - transmittance) + transmittedColor * (hit.mat.ks)
			* transmittance;

	c.clamp();
	return c;
}
