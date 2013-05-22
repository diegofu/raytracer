#ifndef _BUMP_MAPPING_
#define _BUMP_MAPPING_

#include "ImageTexture.h"
#include "Image.h"
#include "rgb.h"
class Image;
class BumpMapping:public ImageTexture{
public:
	BumpMapping(){
		mapped = false;
	}
	BumpMapping(string filename, string filename2);
	Vector3 getNormal(double u, double v);
	Image *normalImage;
	bool mapped;



};

#endif
