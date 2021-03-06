#ifndef __OPERATIONS__
#define __OPERATIONS__

#include <math.h>

#ifndef PI
#define PI 3.14159265358979323846
#endif

static double rad2deg(double rad) {
	return rad*360.0/(2*PI);
};

static double deg2rad(double deg) {
	return deg*2*PI/360.0;
};

///////////////////////////////////////////////////////////////////////////

#endif
