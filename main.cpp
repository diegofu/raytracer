#include <vector>
#include <iostream>
#include "Vector3.h"
#include "rgb.h"
#include "Image.h"
#include "Shape.h"
#include "Triangle.h"
#include "FileParser.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "Raytrace.h"
using namespace std;

int
	main(int argc, const char* argv[])
{

	//taking in arguement from command line
	char *filename = new char[40];
    strcpy(filename,argv[1]);

    Raytrace r(filename);
    free(filename);
    printf("finished\n");
	return 0;
}
