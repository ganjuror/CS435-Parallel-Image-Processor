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

	Last Modified: March 28, 2012
*/





#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
int main()
{
	   time_t start, stop; // Variables that will interact with clock()
	   clock_t ticks;   // Number of clock ticks
	   long count;

	int number_entered;	// int that holds the selection the user wants to make
	char pic_name[50];  //string array to hold name of the picture the user wants to select
	int num_nodes;		//Int to hold the number of nodes the user wants to run the function on
	int i;  //Stores the length of entered strings


	printf ("**********************************************\n");
	printf ("WELCOME TO THE IMAGE EDITOR OF THE FUTURE \n");
	printf ("**********************************************\n");
	printf ("Please enter a number to select from the following choices: \n");
	printf ("Enter 1 to blur an image: \n");
	printf ("Enter 2 to negate an image: \n");
	printf ("Enter 3 to derp an image: \n");
	scanf("%d", &number_entered );
	printf("You selected: %d \n", number_entered);
	
	if(number_entered == 1)
	{
		printf("\n");
		printf("**************************************\n");
		printf("BLUR EDITOR TOOL \n");
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
    	while(fgets(path, sizeof(path)-1, fp) != NULL){
      	printf("%s", path);

    	}

    /*close */
    pclose(fp);
	
	//************ END OF LS COMMAND ************************
		printf("\n");
		printf("Please select an image to blur: ");
		scanf ("%[^\n]s", pic_name);
		i= strlen(pic_name);
		printf("You selected %s %d as your picture\n", pic_name);
		printf("How many nodes should this run on? ");
		scanf("%d", &num_nodes);
		printf("You selected %d nodes \n", num_nodes);
		
		/* Do lotsa fancy calculations */
		
		// THE FOLLOWING IS JUST TO SHOW HOW THE TIMER WORKS.  UNCOMMENT TO TEST THE CLOCK!!!
	   /*
	   int j = 0;
		
	   // Start timer 
	   time(&start);
			
	   while(j<100000)
	   {
		   printf("Work work %d\n", j);
		   j++;
		   ticks = clock();	 
	   }
 
		// Stop timer 
		time(&stop);

	    printf("Used %0.2f seconds of CPU time. \n", (double)ticks/CLOCKS_PER_SEC);
	    printf("Finished in about %.0f seconds. \n", difftime(stop, start));
	   */	   
	}
	else if(number_entered == 2)
	{
		printf("\n");
		printf("**************************************\n");
		printf("NEGATE EDITOR TOOL \n");
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
      	//exit;

    	}

    	/*Read the output a line at a time */
    	while(fgets(path, sizeof(path)-1, fp) != NULL){
      	printf("%s", path);

    	}

    /*close */
    pclose(fp);
	
	//************ END OF LS COMMAND ************************
		printf("\n");
		printf("Please select an image to negate: ");
		scanf ("%[^\n]s", pic_name);
		i= strlen(pic_name);
		printf("You selected %s %d as your picture\n", pic_name);
		printf("How many nodes should this run on? ");
		scanf("%d", &num_nodes);
		printf("You selected %d nodes \n", num_nodes);

		/* Do lotsa fancy calculations */
		
		// THE FOLLOWING IS JUST TO SHOW HOW THE TIMER WORKS.  UNCOMMENT TO TEST THE CLOCK!!!
	   /*
	   int j = 0;
		
	   // Start timer 
	   time(&start);
			
	   while(j<100000)
	   {
		   printf("Work work %d\n", j);
		   j++;
		   ticks = clock();	 
	   }
 
		// Stop timer 
		time(&stop);

	    printf("Used %0.2f seconds of CPU time. \n", (double)ticks/CLOCKS_PER_SEC);
	    printf("Finished in about %.0f seconds. \n", difftime(stop, start));
	   */
	}
	else if(number_entered == 3)
	{
		printf("\n");
		printf("**************************************\n");
		printf("SOME OTHER FUNCTION EDITOR TOOL \n");
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
      	//exit;

    	}

    	/*Read the output a line at a time */
    	while(fgets(path, sizeof(path)-1, fp) != NULL){
      	printf("%s", path);

    	}

    /*close */
    pclose(fp);
	
	//************ END OF LS COMMAND ************************
		printf("\n");
		printf("Please select an image to do SOMETHING TO: ");
		scanf ("%[^\n]s", pic_name);
		i= strlen(pic_name);
		printf("You selected %s %d as your picture\n", pic_name);
		printf("How many nodes should this run on? ");
		scanf("%d", &num_nodes);
		printf("You selected %d nodes \n", num_nodes);
	
		/* Do lotsa fancy calculations */
		
		// THE FOLLOWING IS JUST TO SHOW HOW THE TIMER WORKS.  UNCOMMENT TO TEST THE CLOCK!!!
	   /*
	   int j = 0;
		
	   // Start timer 
	   time(&start);
			
	   while(j<100000)
	   {
		   printf("Work work %d\n", j);
		   j++;
		   ticks = clock();	 
	   }
 
		// Stop timer 
		time(&stop);

	    printf("Used %0.2f seconds of CPU time. \n", (double)ticks/CLOCKS_PER_SEC);
	    printf("Finished in about %.0f seconds. \n", difftime(stop, start));
	   */
	}



	return 0;

}
