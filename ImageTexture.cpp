#include "ImageTexture.h"

ImageTexture::ImageTexture(string filename) {
	image = new Image();
	image->readPPM(filename);

}

Vector3 ImageTexture::getNormal(double u, double v) {
	return Vector3(0, 0, 0);
}
rgb ImageTexture::getColor(double _u, double _v) {
	double u = _u - int(_u);
	double v = _v - int(_v);
	u *= (image->getWidth() - 3);
	v *= (image->getHeight() - 3);

	int iu = ((int) u);
	int iv = ((int) v);

	double tu = u - iu;
	double tv = v - iv;

	//anti aliased texture

	rgb c = image->color(iu, iv) * (1 - tu) * (1 - tv) + image->color(iu + 1,
			iv) * tu * (1 - tv) + image->color(iu, iv + 1) * (1 - tu) * tv
			+ image->color(iu + 1, iv + 1) * tu * tv;

//	rgb c = image->color(iu,iv);
	return c;

}
