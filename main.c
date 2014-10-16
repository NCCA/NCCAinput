#include <stdio.h>
#include <stdlib.h>
#include "input.h"

void showColours();
void showInput();

int main()
{
	printf("Demo of the ncca C input library\n");
	showColours();
	printf("\nIt can get different input\n");
	showInput();
	printf("Press anykey to clear the screen\n");
	while(!kbhit());
	clearscreen();

	printf("finally reset the terminal\n");
	clearInput();
	echoOn();
	unblockTerminal();


	return EXIT_SUCCESS;
}

void showColours()
{
	setColour(RED);
	printf("It does ");
	setColour(GREEN);
	printf("Colours \n");
	setColour(NORMAL);
	printf("setColour(NORMAL)\n");
	setColour(RED);
	printf("setColour(RED)\n");
	setColour(GREEN);
	printf("setColour(GREEN)\n");
	setColour(YELLOW);
	printf("setColour(YELLOW)\n");
	setColour(BLUE);
	printf("setColour(BLUE)\n");
	setColour(MAGENTA);
	printf("setColour(MAGENTA)\n");
	setColour(CYAN);
	printf("setColour(CYAN)\n");
	setColour(WHITE);
	printf("setColour(WHITE)\n");
	setColour(RESET);
	printf("setColour(RESET)\n");

}



void showInput()
{
	float f;
	char c;
	int i;
	printf("enter an int>");
	i=getInt();
	printf("You entered %d\n",i);
	printf("enter a float>");
	f=getFloat();
	printf("You entered %f\n",f);
	printf("By unblocking the terminal we can get continuous chars");
	printf("for this example we turn off echo and convert lower to upper esc to quit\n");
	echoOff();
	unblockTerminal();
	do
  {
    // get a char
    c=getSingleCharUpper();	
    if(c==27) //esc
     break;
    printf("%c",c);
	}while(!kbhit());
	blockTerminal();
	echoOn();
}



