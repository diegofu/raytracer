// Image.h

#ifndef _IMAGE_H_
#define _IMAGE_H_ 1

#include <cmath>
#include <string>
#include <fstream>
#include <istream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "rgb.h"
using namespace std;

class Image
{
public:
  Image();
  // initializes raster to default rgb color
  Image(int width, int height );
  // initializes raster to 'background'
  Image(int width, int height, rgb background);
  // returns false if x or y are out of bounds, else true

  bool set(int x, int y, const rgb& rgb);
  void gammaCorrect(float gamma);
  // outputs PPM image to 'out'
  void writePPM(const char* filename);
  void readPPM (string file_name);

  rgb color(int x, int y);

  int getWidth();
  int getHeight();

  FILE *file;
  rgb** raster;
  int nx;  // raster width
  int ny;  // raster height
};

#endif // _IMAGE_H_
