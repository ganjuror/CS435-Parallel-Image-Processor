/* 
	Program: Main program (calls subfunction)
	Author:David Dvorak, Shaun Piazza
	Purpose:allows user input to select an input file, a filter, and whether or not it should run parallel, it should then output a file named 			output.png with the applied filter

***********************************************************NOTICE************************************************************************************
This file is for iteration two only.  The only things left on the to-do list are:

	1.move redfilter to an external file
	2.add the pragmas to redfilter
	3.Fix the Node_array section as it doesn't pertain to what we are doing anymore
	4.Add logic so if not running in parallel, no pragmas will be used.




	Last Modified: April 18, 2012
*/


#include <omp.h>
#include <Magick++.h>
#include <Magick++/Image.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define INPUTLEN 4
#define PICLEN 50
#define CHECKLEN 50

using namespace Magick;
using namespace std;

// global string array that holds all images in current directory to check against user input
string pic_check[CHECKLEN];

//printFiles() expects no arguments and prints all files in users current working directory
void printFiles();
//Redfilter expects a filename which the user is prompted for below
void redfilter(string filename);
//toGrayscale expect a filename (.png) which the user is propted for below and creates a file out that is a grayscale version of the input
void toGrayscale(string filename);
// user selection validation function
bool validateSelection(char user_input, char acceptable_input[20]);

// Need to rename main() for CUTE testing to avoid conflict with CUTE main...
int FOOmain()
{	
	char pic_name[PICLEN];  // character array to hold name of the picture the user wants to select
	char input_array[INPUTLEN];
	char node_array[INPUTLEN];
	bool correctImage = false;
	int i;  // Stores the length of entered strings
	string curName; // string to hold the current user input	
	struct timeval start, end;
	long mtime, seconds, useconds; 	

	printf ("**********************************************\[0]n");
	printf ("WELCOME TO THE IMAGE EDITOR OF THE FUTURE \n");
	printf("**************************************\n");
	printf("Here are all of the PNG files in your current directory: \n\n");

	printFiles();	
	
	printf("\nPlease select an image to filter: ");

	while(correctImage == false)
	{
		// Store the entered value into a string
		 curName = fgets(pic_name,PICLEN, stdin);
		
		// Check each value in pic_check to see if it matches curName	
		for(int j = 0; j < CHECKLEN; j++)
		{
			// If what the user typed in is an image in the directory, we have a match
			if(curName == pic_check[j])
			{
				correctImage = true;
				
				// This loop strips off the newline character that fgets puts on the input and makes it a null character
				for ( i = 0; i < PICLEN; i++ ) 
				{
					if ( pic_name[i] == '\n' ) 
					{
						pic_name[i] = '\0';
						break;
					}
				}		
			}
		}
		
		// If no match was found, ask for another input
		if(correctImage == false)
		{
			printf("Image not found.  Please select another image: ");
		}
	}
	
	printf("You selected %s as your picture\n", pic_name);	
	/* "Unit test" */
	printf("EXPECTED: %s ACTUAL: %s\n", pic_name, pic_name);
	/* End of test */
	
	printf ("**********************************************\n");
	printf ("Please enter a number to select from the following choices: \n");
	printf ("Enter 1 to Red Filter your image.\n");
	printf ("Enter 2 to Grayscale Filter your image.\n");
	
	fgets(input_array,INPUTLEN, stdin);
	
	for ( i = 0; i < INPUTLEN; i++ ) 
	{
		if ( input_array[i] == '\n' ) 
		{
			input_array[i] = '\0';
			break;
		}
	}
	
	printf("You selected %s! \n", input_array);
	/* "Unit test" */
	printf("EXPECTED: 1 or 2, ACTUAL: %s\n", input_array);
	/* End of test */
	
	
	/* ERROR CHECKING LOOP */
//	while((input_array[0] != '1') && (input_array[0] != '2'))
	char good_input[3] = {'1','2'};
	while(!validateSelection(input_array[0], good_input))
	{
		printf ("**********************************************\n");
		printf ("You entered an incorrect value, please try again.\n");
		printf ("Please enter a number to select from the following choices: \n");
		printf ("Enter 1 to Red Filter your image.\n");
		printf ("Enter 2 to Grayscale Filter your image.\n");
	
		fgets(input_array,INPUTLEN, stdin);
		
		for ( i = 0; i < INPUTLEN; i++ ) 
		{
			if ( input_array[i] == '\n' ) 
			{
				input_array[i] = '\0';
				break;
			}
		}	
	
		printf("You selected %s! \n", input_array);
	}
	/* **** END ERROR CHECKING LOOP **** */
	
	if(input_array[0] == '1')
	{
		printf("\n");
		printf("**************************************\n");
		printf("RED FILTER TOOL \n");

		printf("\n");

		printf("Would you like to run this in parallel?\n");
		printf("y or n: \n");
		
		fgets(node_array,INPUTLEN, stdin );
		
		for ( i = 0; i < INPUTLEN; i++ ) 
		{
			if ( node_array[i] == '\n' ) 
			{
				node_array[i] = '\0';
				break;
			}
		}		
		
		printf("You selected %s \n", node_array);
		/* "Unit test" */
		printf("EXPECTED: yes or no ACTUAL: %s\n", node_array);
		/* End of test */
		
		/* ERROR CHECKING LOOP */
		char good_input[4] = {'y','n','Y','N'};
		while(!validateSelection(input_array[0], good_input))
		{
			printf ("**********************************************\n");
			printf ("You entered an incorrect value, please try again.\n");
			printf("Would you like to run this in parallel?\n");
			printf("y or n: \n");
		
			fgets(input_array,INPUTLEN, stdin);

			for ( i = 0; i < INPUTLEN; i++ )
			{
				if ( input_array[i] == '\n' )
				{
					input_array[i] = '\0';
					break;
				}
			}

			printf("You selected %s! \n", input_array);
		}
		/* **** END ERROR CHECKING LOOP **** */

		if(node_array[0] == 'y' || node_array[0] == 'Y')
		{
			#pragma omp parallel
			{
				gettimeofday(&start, NULL);
				
				//Call redfilter with pic_name as its parameter
				redfilter(pic_name);
				// Uncomment the usleep() function below to test the timer
				//usleep(9000);
				
				gettimeofday(&end, NULL);

				seconds  = end.tv_sec  - start.tv_sec;
				useconds = end.tv_usec - start.tv_usec;

				mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

				printf("Elapsed time: %ld milliseconds\n", mtime);
			}
		}
		else
		{
			gettimeofday(&start, NULL);
			
			//Call redfilter with pic_name as its parameter
			redfilter(pic_name);
			// Uncomment the usleep() function below to test the timer
			//usleep(9000);
			
			gettimeofday(&end, NULL);

			seconds  = end.tv_sec  - start.tv_sec;
			useconds = end.tv_usec - start.tv_usec;

			mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

			printf("Elapsed time: %ld milliseconds\n", mtime);		
		}


	}
	
	if(input_array[0] == '2')
	{
		printf("\n");
		printf("**************************************\n");
		printf("GRAYSCALE TOOL\n");

		printf("\n");

		printf("Would you like to run this in parallel?\n");
		printf("y or n: \n");
		
		fgets(node_array,INPUTLEN, stdin );
		
		for ( i = 0; i < INPUTLEN; i++ ) 
		{
			if ( node_array[i] == '\n' ) 
			{
				node_array[i] = '\0';
				break;
			}
		}		
		
		printf("You selected %s \n", node_array);
		/* "Unit test" */
		printf("EXPECTED: yes or no ACTUAL: %s\n", node_array);
		/* End of test */

		/* ERROR CHECKING LOOP */
		char good_input[4] = {'y','n','Y','N'};
		while(!validateSelection(input_array[0], good_input))
		{
			printf ("**********************************************\n");
			printf ("You entered an incorrect value, please try again.\n");
			printf("Would you like to run this in parallel?\n");
			printf("y or n: \n");

			fgets(input_array,INPUTLEN, stdin);

			for ( i = 0; i < INPUTLEN; i++ )
			{
				if ( input_array[i] == '\n' )
				{
					input_array[i] = '\0';
					break;
				}
			}

			printf("You selected %s! \n", input_array);
		}
		/* **** END ERROR CHECKING LOOP **** */
		
		if(node_array[0] == 'y' || node_array[0] == 'Y')
		{
			#pragma omp parallel
			{
				gettimeofday(&start, NULL);
				
				//Call redfilter with pic_name as its parameter
				toGrayscale(pic_name);
				// Uncomment the usleep() function below to test the timer
				//usleep(9000);
				
				gettimeofday(&end, NULL);

				seconds  = end.tv_sec  - start.tv_sec;
				useconds = end.tv_usec - start.tv_usec;

				mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

				printf("Elapsed time: %ld milliseconds\n", mtime);
			}
		}
		else
		{
			gettimeofday(&start, NULL);
			
			//Call redfilter with pic_name as its parameter
			toGrayscale(pic_name);
			// Uncomment the usleep() function below to test the timer
			//usleep(9000);
			
			gettimeofday(&end, NULL);

			seconds  = end.tv_sec  - start.tv_sec;
			useconds = end.tv_usec - start.tv_usec;

			mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

			printf("Elapsed time: %ld milliseconds\n", mtime);		
		}


	}

}

bool validateSelection(char user_input, char acceptable_input[20])
{
	int i = 0;
	while ((acceptable_input[i] != '\0') && (acceptable_input[i] != '\n') && i<20)
	{
		if (acceptable_input[i] == user_input) return true;
		i++;
	}
	return false; // user input matches nothing from acceptable_input[]
}

////////////////////////////////////////////////END MAIN//////////////////////////////////////////////////////////////////

	/*WE WILL MOVE THIS TO ANOTHER FILE BUT IM HACKING THE CRAP OUT OF IT RIGHT NOW :
		This is a section of code that executes the ls command on a given directory
		*/
void printFiles()
{
		FILE *fp;
	    	int status;
			int count = 0;
	    	char path[1035];

	    	/*open the command for reading. */
			
			/*  The following commented code was removed from a previous version of the ls command
			 * ~/project/
			*/		
			
	    	fp = popen("/bin/ls *.png", "r");		//Open ls command and run it on the given directory
	    	if(fp ==NULL)
	    	{
	      		printf("Failed to run command \n");
	    	}

	    	/*Read the output a line at a time */
	    	while(fgets(path, sizeof(path)-1, fp) != NULL)
			{
				printf("%s", path);
				pic_check[count] = path;		
				count++;
	    	}

		/*close */
		pclose(fp);
	
	//************ END OF LS COMMAND ************************
}

/*This needs to be moved to an external file at some point, but for now it works! */
void redfilter(string filename)
{
	
	
	//make an image called inputter that we will use as the input image
	Image inputter;
	//make an image called output that we will use as the output image
	Image output;
	//read the passed in filename
	inputter.read(filename);
	
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

}

/* This function takes a filename as an argument (must be .png) and creates a file called gray_output.png that is a grayscale
version of the argument file */

void toGrayscale(string filename)
{
	
	
	//make an image called inputter that we will use as the input image
	Image inputter;
	//make an image called output that we will use as the output image
	Image output;
	//read the passed in filename
	inputter.read(filename);
	
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
	Quantum graycolor; 

	//For every single pixel
	for(ssize_t i=0; i< columns*rows; i++)
	{

		//We will acomplish the grayscale setting all the RGB values to the same value as determined by recomendation BT.709
		//"Basic Parameter Values for the Studio and International Programme Exchange"

		//Setting graycolor to ITU-R recomendation
		graycolor = all_pixels[i].red * 0.2125 + all_pixels[i].green * 0.7154 + all_pixels[i].blue * 0.0721;

		all_pixels[i].red = graycolor;
		all_pixels[i].green = graycolor;
		all_pixels[i].blue = graycolor;
		all_pixels[i].opacity= 0;
					
	}
	//Sync the pixels up
	inputter.syncPixels();
	//output the new image to a file called gray_output.png
	inputter.write("gray_output.png");
}
