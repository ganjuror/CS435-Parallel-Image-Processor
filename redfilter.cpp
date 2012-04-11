#include <Magick++.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#define INPUTLEN 4
#define PICLEN 50

using namespace Magick;
using namespace std;


int main()
{
	
	
	//make an image called test that we will use as the input image
	Image test;
	//make an image called output that we will use as the output image
	Image output;
	//load the ball.png into the input image
	test.read("ball.png");
	
	//Get the number of columns and rows in the image
	int columns =test.columns();
	int rows = test.rows();
	
	//make image Direct class so we can access the colors of each pixel (because pngs are funkayyy)
	test.classType(DirectClass);
	
	//Set this bad boy up for manipulation	
	test.modifyImage();
	
	//Allocate some memories for each pixel
	PixelPacket *all_pixels = test.getPixels(0,0,columns, rows);

	//Make a place to grab the rgba values
	Quantum red, green, blue, opacity; 

	//For every single pixel
	for(ssize_t i=0; i< columns*rows; i++)
	{
	      	      
		red = all_pixels[i].red;         // grab the red value
		green = all_pixels[i].green;  // grab the green value
		blue = all_pixels[i].blue;      // grab the blue value
		opacity = all_pixels[i].opacity;

		//This was for testing but it says if they all are set to something set them to be clear!
		if(red != 0 || blue !=0 || green !=0 || opacity !=0)
		{
			
			all_pixels[i].green = 0;
			all_pixels[i].blue = 0;
			all_pixels[i].red = 0;
			all_pixels[i].opacity= -1;
			
		}
		

	}	
			//Sync the pixels up
			test.syncPixels();
			//output the new image to a file called output.png
			test.write("output.png");







	return 0;

}

