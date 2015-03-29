#ifndef _IO_UTILS_H_
#define _IO_UTILS_H_
// you must have a config file, both for windows and for compiling on Linux (MAMA)
// BUT, you need to change the content of the config!
#include "config.h"
#include "Color.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Point.h"

void gotoxy(int x, int y);
void gotoxy(const Point&); // My adding
void setTextColor(Color);
void hideCursor();
void clear_screen();
void writeOnTopOfScreen(std::string sentence="");

const static int LENGH_OF_PAGE = 24; // My adding
const static int LENGH_OF_LINE = 80; // My adding
const static int AMOUNT_OF_INSTRUCTIONS_LINE = 3; // My adding

	#ifndef WINDOWS	
		int _getch(void);
		int _kbhit(void);
		void Sleep(unsigned long);
		void _itoa_s(unsigned int, char s[], unsigned int, int);
		void setTextColor(int);
	#else
		#include <stdlib.h>
		#include <conio.h>
		#include <windows.h>
	#endif

#endif