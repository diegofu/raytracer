Name: Shoucheng(Diego) Fu
Student #: 301099653
CMPT 361 Lab 4: Raytracing

Hi,
I am able to implement all the required functionalities. After typing make in the command line, an executable file called lab4 is produced, and it should be followed by a input render file name (eg. "./lab4 lab4_sample1.txt")
The 5 lab samples are in the primary folder, where as all my other input files and images are in lab4_products.

In addition, I have added the follow effects, and how to use them

	-bump mapping: bumpMap texture_name texture_normal_name

	-texture anti-aliasing: I have using bilinear texture anti-aliasing, but I don't actually have a command to turn in on or off; however, you can see it in my file ImageTexuture.cpp function getColor(). (lab_sample5.ppm is without texture anti-aliasing, where as lab_sample5-texture-aliasing.ppm is within texture anti-aliasing)

	-area light and soft shadow: area_light r g b x y z radius (I've implemented my area light as a spherical luminaire since the shape of the luminaire is less important than the actual shape and easier to be implemented, and I am generating 16 samples for each hit point in order to achieve soft shadow)

	-2d jittering super sampling: jitter numberOfX numberOfY (this will lessen the aliasing of the picture. If we zoom in, we can see big difference; however, takes very long to render the image)

Last but not least, myImage.ppm is my final product for this lab. I've used 3 area lights each has 64 samples to simulate soft shadows. And the middle box is bump mapped with CobbledWall.ppm. I have added 4 spheres with different radii, some of which have different kd and ks values. There is a hanging picture(hope you will see it this way) attached to one of the wall and is bump mapped. There is a cone shape object in the scene as well to simulate complicated triangular objects. Texture anti-aliasing is applied. I shot 16 rays per each pixel with jitter supersampling method.(took me about 30 minutes to render the image). And the image looks to me is pretty nice. Since it takes too much time to render, there is a simpler version names myImage2.ppm and the input file is myImage2.txt. This one only has point_light and only shots 1 ray per pixel, and will be rendered with in a minute.Thank you for marking it.

NOTE:
	Sometimes a black image will be generated. You will just have to render the image one more time. Sorry for that, and I don't know why that occurs.


