#include "Image.h"
#include <iostream>

Image::Image()
{}

Image::Image(int width, int height)
{
	nx = width;
	ny = height;
	
	// allocate memory for raster
	raster = new rgb* [nx];
	for (int i = 0; i < nx; i++){
		raster [i] = new rgb [ny];
	}


}

Image::Image(int width, int height, rgb background)
{
	nx = width;
	ny = height;

	// allocate memory for raster

	raster = new rgb*[nx];
	for (int i = 0; i < nx; i++)
	{
		raster [i] = new rgb[ny];

		// assign 'background' to each element
		for (int j = 0; j < ny; j++)
			raster [i][j] = background;
	}
}


bool Image::set(int x, int y, const rgb& color)
{
	// check for out of bounds error
	if (0 > x || x > nx) return false;
	if (0 > y || y > ny) return false;

	raster [x][y] = color;
	return true;
}

void Image::gammaCorrect(float gamma)
{
	rgb temp;
	float power = 1.0 / gamma;
	for (int i = 0; i < nx; i++)
		for (int j = 0; j < ny; j++)
		{
			temp = raster[i][j];
			raster[i][j] = rgb(pow(temp._r, power),
				pow(temp._g, power),
				pow(temp._b, power));
		}
}

void Image::writePPM(const char *filename)
{

	unsigned int ired, igreen, iblue;

	
        int i, j;

		
	
        FILE * fp = fopen(filename, "wb"); /* b - binary mode */

        fprintf(fp, "P6\n%d %d\n255\n", nx, ny);
		for (j=0; j<ny; ++j) {
			for (i=0; i<nx; ++i) {
				ired = (unsigned int)(255*raster[i][j]._r);
				igreen = (unsigned int)(255*raster[i][j]._g);
				iblue = (unsigned int)(255*raster[i][j]._b);
				static unsigned char color[3];
				color[0] = (ired>255)?255:ired; /* red */
                        color[1] = (igreen>255)?255:igreen; /* green */
                        color[2] = (iblue>255)?255:iblue; /* blue */
                        fwrite(color,1,3,fp);
                }
        }
        fclose(fp);
 
}

// reads in a binary PPM
void Image::readPPM(string file_name)
{
	char buf[1024], *t;
	unsigned int w,h,d;
	int r;
	char red, green, blue;
	short int ired, igreen, iblue;
	char* filename = new char[file_name.size()+1];
	strcpy(filename, file_name.c_str());
	FILE *fp = fopen(filename,"r");
	if(!fp){
		exit(-1);
	}
	t = fgets(buf, 1024, fp);
	if(( t ==NULL) || strncmp(buf,"P6\n",3) != 0)exit(-1);

	do{
		t = fgets(buf, 1024, fp);
		if(t == NULL) exit(-1);
	}while(strncmp(buf, "#", 1) ==0 || strncmp(buf, "\n", 1) == 0);
	r = sscanf(buf, "%u %u", &w, &h);
	if(r<2) exit(-1);

	r = fscanf(fp,"%u\n", &d);
	
	nx = w;
	ny = h;
	raster = new rgb*[nx];
	for (int i = 0; i < nx; i++)
		raster[i] = new rgb[ny];

	if(d == 255){
		for (int i = 0; i <ny; i++){
			for (int j = 0; j < nx; j++)
			{
				red = fgetc(fp);
				green = fgetc(fp);
				blue = fgetc(fp);
				raster [j][i] =
					rgb((float)((unsigned char)red)/255.0,
					(float)((unsigned char)green)/255.0,
					(float)((unsigned char)blue)/255.0);
			}
	
		}
	}else{
		for (int i = 0; i <ny; i++){
			for (int j = 0; j < nx; j++){
				red = fgetc(fp);
				ired = red * 256;
				red = fgetc(fp);
				ired += red;



				green = fgetc(fp);
				igreen = green * 256;
				green = fgetc(fp);
				igreen += green;

				blue = fgetc(fp);
				iblue = blue * 256;
				blue = fgetc(fp);
				iblue += blue;
				raster [j][i] =
						rgb((float)((unsigned short int)ired)/65535,
						(float)((unsigned short int)igreen)/65535,
						(float)((unsigned short int)iblue)/65535);
			}
		}
	}
	fclose(fp);

}

int Image::getHeight(){ return ny;}
int Image::getWidth(){return nx;}

rgb Image::color(int x, int y){
	return raster[x][y];

}
