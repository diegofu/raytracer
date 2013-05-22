# Generic Makefile that should work with any program you're going to compile
# Any complaints should be directed at htw@sfu.ca
# to compile and link your program all you have to do is run 'make' in the
# current directory
# to clean up object files run 'make clean_object'
# to delete any compiled files run 'make clean'

# Where to find the non standard library files
# INCLUDEDIR is where the header files can be found
# LIBDIR is where the library object files can be found
INCLUDEDIR=/usr/local/include/
LIBDIR=/usr/local/lib

# If you have more source files add them here 
HEADER = Camera.h DynArray.h FileParser.h Image.h ImageTexture.h Light.h Material.h mesh.h ONB.h Operations.h Pointlight.h RandomNumberGenerator.h Ray.h Raytrace.h rgb.h Shape.h Sphere.h Triangle.h Vector3.h DynSphere.h DirectionalLight.h BumpMapping.h AreaLight.h
SOURCE= FileParser.cpp Image.cpp ImageTexture.cpp main.cpp Material.cpp mesh.cpp ONB.cpp PointLight.cpp Raytrace.cpp Sphere.cpp Triangle.cpp Vector3.cpp DirectionalLight.cpp DynSphere.cpp BumpMapping.cpp AreaLight.cpp

# The compiler we're using 
CC= g++

# The flags that will be used to compile the object file if you want
# the debug version of your program (say you want to use a debugger), then
# you can add '-g' on the following line
CFLAGS= -O3 -Wall

# The basic library we're using add the other libraries you want to link
# to your program here 
CLIBFLAG= 

# If you have other library files in a different directory add them here 
INCLUDEFLAG= -I. -I$(INCLUDEDIR)
LIBFLAG= -L$(LIBDIR)

# Don't touch this one if you don't know what you're doing 
OBJECT= $(SOURCE:=.o)
#OBJECT= $(SOURCE:.C=.o)

# The name of the final executable 
EXECUTABLE=lab4

# Don't touch any of these either if you don't know what you're doing 
all: $(OBJECT) depend
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECT) $(INCLUDEFLAG) $(LIBFLAG) $(CLIBFLAG)

depend:
	$(CC) -M $(SOURCE) > depend

$(OBJECT):
	$(CC) $(CFLAGS) -c -o $@ $(@:.o=)
#	$(CC) $(CFLAGS) -c -o $@ $(@:.o=.C)

clean_object:
	rm -f *.o
#	rm -f $(OBJECT)

clean:
	rm -f *.o depend $(EXECUTABLE)
# 	rm -f $(OBJECT) depend $(EXECUTABLE)

include depend

