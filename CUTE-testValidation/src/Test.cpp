#include "cute.h"
#include "ide_listener.h"
#include <stdio.h>
#include "cute_runner.h"
#include "ImageProcessor-435Project.h"

void testValidInput() {
	char user_input[20] = {'1','2','3','4'};
	char good_input[20] = {'1','2','3','4'};
	int i = 0;
	while(user_input[i] != '\0' && user_input[i] != '\n' && i<20)
	{
		ASSERTM("Failed Valid Input Test", validateSelection(user_input[i],good_input));
		i++;
	}
}
void testOutOfRange()
{
	char user_input[3] = {'0', '5', '6'};
	char good_input[20] = {'1','2','3','4'};
	int i = 0;
	while ((user_input[i] != '\0') && (user_input[i] != '\n') && i<3)
	{
		//printf("Input tested: %s\n", user_input[i]);
		ASSERTM("Failed Out of Range Test", !validateSelection(user_input[i],good_input));
		i++;
	}
}
void testSpecialCharacters()
{
	char user_input[4] = {'@', '!', '%', '$'};
	char good_input[20] = {'1','2','3', 'a', 'b', 's'};
	int i = 0;
	while ((user_input[i] != '\0') && (user_input[i] != '\n') && i<4)
	{
		ASSERTM("Failed Special Character Test", !validateSelection(user_input[i],good_input));
		i++;
	}
}
void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testValidInput));
	s.push_back(CUTE(testOutOfRange));
	s.push_back(CUTE(testSpecialCharacters));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main(){
    runSuite();
    return 0;
}


