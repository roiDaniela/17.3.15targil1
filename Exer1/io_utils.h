//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// io_utils.h
// -----------
// This file is not a oop class, its responsible to all the io global functions. 
//
// Author: Motty Katz  && Roi Fogler
// First version: 2015-03-18
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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
#include "ScreenData.h"

// NEW CODE EX1, author = <Motty Katz && Roi Fogler>, date = <2015 - 03 - 20>
enum Lines
{
	LINE_ONE_RIGHT = 1,
	LINE_ONE_LEFT,
	LINE_ONE_MIDDLE,
	LINE_TWO_RIGHT,
	LINE_TWO_LEFT,
	LINE_THREE_RIGHT,
	LINE_THREE_LEFT
};

void gotoxy(int x, int y); // already givven
void gotoxy(const Point&);
void setTextColor(Color); // already givven
void hideCursor(); // already givven
void clear_screen(); // already givven
void CleanTopOfScreen();
void CleanScreenAtPoint(const Point& p);
void CleanScreenAtPoint(int x, int y);
void CleanScreenAtPoint(int x, int y);
void writeOnScreenLocation(Lines, std::string sentence = "");
void RefreshScreen(const map<Point, int>& DataBase, const Point& player1Loc, const Point& player2Loc);

const static int LENGH_OF_PAGE = 24;
const static int LENGH_OF_LINE = 80; 
const static int AMOUNT_OF_INSTRUCTIONS_LINE = 3; 
// END OF NEW CODE EX 1

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