#ifndef _IMAGE_TEXTURE_
#define _IMAGE_TEXTURE_

#include "Vector3.h"
#include "rgb.h"
#include "Image.h"
#include <string>
class Image;
class ImageTexture{
public:
	ImageTexture(){}
	ImageTexture(string filename);
	rgb getColor(double u, double v);
	virtual Vector3 getNormal(double u, double v);
	Image *image;
};


#endif
