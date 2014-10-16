#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include "input.h"


// from http://stackoverflow.com/questions/3585846/color-text-in-terminal-aplications-in-unix
void setColour(enum Colours c)
{

	switch(c)
	{
		case NORMAL : printf("\x1B[0m"); break;
		case RED : printf("\x1B[31m"); break;
		case GREEN : printf("\x1B[32m"); break;
		case YELLOW : printf("\x1B[33m"); break;
		case BLUE : printf("\x1B[34m"); break;
		case MAGENTA : printf("\x1B[35m"); break;
		case CYAN : printf("\x1B[36m"); break;
		case WHITE : printf("\x1B[37m"); break;
		case RESET : printf("\033[0m"); break;
		default : printf("\033[0m"); break;
	}



}

/// this code is from http://cc.byexamples.com/2007/04/08/non-blocking-user-input-in-loop-without-ncurses/
/// and http://stackoverflow.com/questions/19875136/continuous-keyboard-input-in-c
int kbhit()
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

enum BlockState{NB_DISABLE,NB_ENABLE};
static int s_termState=NB_DISABLE;

void nonblock(enum BlockState state)
{
    struct termios ttystate;
 
    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);
 
    if (state==NB_ENABLE)
    {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
        s_termState=NB_ENABLE;
    }
    else if (state==NB_DISABLE)
    {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
        s_termState=NB_DISABLE;

    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
 
}


void blockTerminal()
{
	nonblock(	NB_ENABLE);
}

void unblockTerminal()
{
	nonblock(NB_DISABLE);
}


int getInt()
{
	int initialState=s_termState;
	
	if(s_termState ==NB_DISABLE)
		unblockTerminal();
	
	char line[50];
	fgets(line, sizeof(line), stdin);
	char *ptr;
	int ret = strtol(line, &ptr, 10);
	fflush(stdin);
	clearInput();
	if(initialState ==NB_DISABLE)
		blockTerminal();
	return ret;	
}


// standard getting of input from terminal
char getSingleChar()
{

  int c=(char)fgetc(stdin);
	return c;
}

// standard getting of input from terminal
char getSingleCharUpper()
{

  int c=(char)fgetc(stdin);
	return toupper(c);
}

// standard getting of input from terminal
char getSingleCharLower()
{

  int c=(char)fgetc(stdin);
	return tolower(c);
}
// modified from http://stackoverflow.com/questions/6856635/hide-password-input-on-terminal
int echoOn()
{
	struct termios t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
			return -1;

	t.c_lflag |= (ECHO | ECHOE | ECHOK | ECHONL);

	if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == -1)
			return -1;
			
	return 0;
}

int echoOff()
{
	struct termios t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
			return -1;

	t.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);

	if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == -1)
			return -1;
	return 0;

}
	
	
// modified from http://faq.cprogramming.com/cgi-bin/smartfaq.cgi?id=1043284392&answer=1044873249	
void clearInput()
{
int ch;
while ((ch = getchar()) != '\n' && ch != EOF);
}

// modified from 	
void clearscreen()
{
  const char* CLEAR_SCREE_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO,CLEAR_SCREE_ANSI,12);
}

	
	
	