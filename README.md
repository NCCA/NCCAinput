#NCCA C Input Library
This is a minimal c style input library to help with basic console programming tasks.

A simple demo program is included in [main.c](https://github.com/NCCA/NCCAinput/blob/master/main.c) showing some of the functions in action.  It can be compiled using the following command line

```c
clang -Wall -g main.c input.c -o inputTest
```

It has the following functions

```c
/// @brief block the terminal so it will wait for user input (usually terminal waits for a return)
extern void blockTerminal();
/// @brief unblock the terminal (default)
extern void unblockTerminal();
/// @brief wait for the keyboard to be pressed
/// @returns int non-zero if keyboard is pressed 
extern int kbhit();
/// @brief get a single char from the input stream
/// @returns the char pressed
extern char getSingleChar();
/// @brief get a single char from the input and convert to upper case
/// @returns the char pressed
extern char getSingleCharUpper();
/// @brief get a single char from the input and convert to lower case
/// @returns the char pressed
extern char getSingleCharLower();
/// @brief attempt to get an int from the stream (NONBLOCKING)
extern int getInt();
/// @brief attempt to get an float from the stream (NONBLOCKING)
float getFloat();

/// @brief turn terminal echo On (default is on)
extern int echoOn();
/// @brief turn terminal echo off (don't print input keys)
extern int echoOff();
/// @brief clear the input stream (flush)
extern void clearInput();
/// @brief clear the screen
extern void clearscreen();
/// @brief an enumeration of colours to use when printing
enum Colours{NORMAL,RED,GREEN ,YELLOW,BLUE,MAGENTA,CYAN,WHITE,RESET};
/// @brief set the terminal colour for printing (will remain until changed)
extern void setColour(enum Colours c);


```