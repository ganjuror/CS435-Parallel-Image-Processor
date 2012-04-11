/* Main program to call the functions for each image filter.  This expects no parameters and uses user input and output to 
help the user make their selection.  The program consists of 2-3 parts:
	part 1: Show the user they have entered the editor, and show the possible selections
	part 2: Based on the user's selection, it shows them their selection, then prints all the images in their image directory
	(which I am assuming are the possible choices), and then asks for the user to select a given image.
	part 3: based on the selected image a function is called to do the selected filter.

	Thats as far as I've gotten so far.


	SIDE NOTE:  Right now this only runs on Unix based systems, since we will be using nrs-projects it will work, I haven't tested it
	on my mac but all you would have to change is the directory that the ls command is stored in (if it is stores somewhere different),
	it also assumes that the folder you are storing the images in are in ~/Dropbox/Project.  If you want to run it on your computers then
	just change the directory.

	**I cant get it to return the right string and I'm bored and hungry Ill fix it later.


	Program: Main program (calls subfunctions)
	Author:David Dvorak, Shaun Piazza
	Purpose:allows user input to select an input file, a filter, and whether or not it should run parallel




	Last Modified: April 10, 2012
*/



#include <Magick++.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define INPUTLEN 4
#define PICLEN 50


using namespace Magick;
using namespace std;


void redfilter();






int main()
{	
	char pic_name[PICLEN];  //string array to hold name of the picture the user wants to select
	char input_array[INPUTLEN];
	char node_array[INPUTLEN];
	int i;  //Stores the length of entered strings
	struct timeval start, end;
	long mtime, seconds, useconds; 	


	printf ("**********************************************\n");
	printf ("WELCOME TO THE IMAGE EDITOR OF THE FUTURE \n");
	printf ("**********************************************\n");
	printf ("Please enter a number to select from the following choices: \n");
	printf ("Enter 1 to Red Filter an image: \n");
	fgets(input_array,INPUTLEN, stdin );
	
	for ( i = 0; i < INPUTLEN; i++ ) 
	{
		if ( input_array[i] == '\n' ) 
		{
			input_array[i] = '\0';
			break;
		}
	}		
	
	printf("You selected %s! \n", input_array);
	
	if(input_array[0] == '1')
	{
		printf("\n");
		printf("**************************************\n");
		printf("RED FILTER TOOL \n");
		printf("**************************************\n");
		printf("Here are all the files located in your image directory: ");


		/*WE WILL MOVE THIS TO ANOTHER FILE BUT IM HACKING THE CRAP OUT OF IT RIGHT NOW :
		This is a section of code that executes the ls command on a given directory
		*/
		FILE *fp;
	    	int status;
	    	char path[1035];

	    	/*open the command for reading. */
	    	fp = popen("/bin/ls ~/project", "r");		//Open ls command and run it on the given directory
	    	if(fp ==NULL)
	    	{
	      		printf("Failed to run command \n");
	    	}

	    	/*Read the output a line at a time */
	    	while(fgets(path, sizeof(path)-1, fp) != NULL)
		{
			printf("%s", path);
	    	}

		/*close */
		pclose(fp);
	
	//************ END OF LS COMMAND ************************
		printf("\n");
		printf("Please select an image to Red Filter: ");
		fgets(pic_name,PICLEN, stdin);
		
		for ( i = 0; i < PICLEN; i++ ) 
		{
			if ( pic_name[i] == '\n' ) 
			{
				pic_name[i] = '\0';
				break;
			}
		}
		
		printf("You selected %s as your picture\n", pic_name);
		printf("Would you like to run this in parallel? \n");
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
		
		gettimeofday(&start, NULL);
		
		//Now we would call the function that does the red filter

		//NOTE: we need to eventually let this function take a filename as input but for now lets keep it void.	
		redfilter();
		// Uncomment the usleep() function below to test the timer
		//usleep(9000);
		
		gettimeofday(&end, NULL);

	    	seconds  = end.tv_sec  - start.tv_sec;
		useconds = end.tv_usec - start.tv_usec;

		mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

		printf("Elapsed time: %ld milliseconds\n", mtime);


	}

}

////////////////////////////////////////////////END MAIN//////////////////////////////////////////////////////////////////



void redfilter()
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

}









