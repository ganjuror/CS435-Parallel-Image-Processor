/*	Program name: redfilter.cpp
*	Author: David Dvorak
*	Purpose: The purpose of redfilter is to take an image as input, and output a new image called "output.png" with only the pixels
*		 from the original image that had red values associated with them.
*
*	Expected Outcome: a file will be created called "output.png" in the same directory that you ran the function in and it will 
*			  only have red values associated with it.
*
*
*	Last Modified: April 10, 2012
*
*
*/



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
	
	
	//make an image called inputter that we will use as the input image
	Image inputter;
	//make an image called output that we will use as the output image
	Image output;
	//load the tester.png into the input image
	inputter.read("tester.png");
	
	//Get the number of columns and rows in the image
	int columns =inputter.columns();
	int rows = inputter.rows();
	
	//make image Direct class so we can access the colors of each pixel (because pngs are funkayyy)
	inputter.classType(DirectClass);
	
	//Set this bad boy up for manipulation	
	inputter.modifyImage();
	
	//Allocate some memories for each pixel
	PixelPacket *all_pixels = inputter.getPixels(0,0,columns, rows);

	//Make a place to grab the rgba values
	Quantum red, green, blue, opacity; 

	//For every single pixel
	for(ssize_t i=0; i< columns*rows; i++)
	{

		/*These next 4 calls grab the red, green, blue and "alpha" values from each channel
		 *This is strictly so for testing purposes and so we can print them to the screen to
		 *see how they work.									
		 */
	      	      
		red = all_pixels[i].red;         
		green = all_pixels[i].green;  
		blue = all_pixels[i].blue;     
		opacity = all_pixels[i].opacity;

		
		//Cancel out all values but red, we will get only the red values out of the image
		all_pixels[i].green = 0;
		all_pixels[i].blue = 0;
		all_pixels[i].opacity= 0;
				
		
	}
	
	//Sync the pixels up
	inputter.syncPixels();
	//output the new image to a file called output.png
	inputter.write("output.png");

	return 0;

}

