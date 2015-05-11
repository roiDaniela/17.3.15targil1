//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// io_utils.cpp
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

#include "io_utils.h"
#include "Color.h"
#include <map>

using namespace std;

#ifndef WINDOWS
	void gotoxy(int x, int y) {}
	int _getch(void){return 0;}
	int _kbhit(void){return 0;}
	void Sleep(unsigned long){}
	void setTextColor(int color){}
	void hideCursor(){}
	void clear_screen(){}
#else

// NEW CODE EX1, author = <Motty Katz && Roi Fogler>, date = <2015 - 03 - 20>
//---------------------------------------------------------------------------------------
// This function refreshs the screen after selecting "continue" in the sub menu
//---------------------------------------------------------------------------------------
void RefreshScreen(const map<Point, int>& DataBase, const Point& player1LocPoint, const Point& player2LocPoint){
	for (map<Point, int>::const_iterator iter = DataBase.cbegin(); iter != DataBase.cend(); iter++){
		gotoxy(iter->first);
		
		// check if its the player location: then print his sign else print the random number
		if (iter->first == player1LocPoint || iter->first == player2LocPoint){
			cout << (char)iter->second;
		}
		else{
			cout << iter->second;
			if (iter->second > ScreenData::TOW_DIGIT_VALUE)
				iter++;
		}
	}
}

//---------------------------------------------------------------------------------------
// this function cleans the first 3 rows for the title/instructions/information 
//---------------------------------------------------------------------------------------
void CleanTopOfScreen(){
	// Go to the top of the screen
	gotoxy(0, 0);

	// Clean the 2 first lines
	for (int j = 0; j < AMOUNT_OF_INSTRUCTIONS_LINE; j++)
	{
		for (int i = 0; i < LENGH_OF_LINE; i++)
		{
			cout << " ";
		}
	}

	gotoxy(0, 3); // back to start location
}

//---------------------------------------------------------------------------------------
// this function cleans the screen at specific point (overloaded)
//---------------------------------------------------------------------------------------
void CleanScreenAtPoint(const Point& p){
	CleanScreenAtPoint(p.getX(), p.getY());
}

//---------------------------------------------------------------------------------------
// this function cleans the screen at specific point
//---------------------------------------------------------------------------------------
void CleanScreenAtPoint(int x, int y){
	gotoxy(x,y);
	cout << " ";
}
//---------------------------------------------------------------------------------------
// this function gets 1/6 locations (line 1 left, line 2 right ... line 2 right) 
// to print the second param: sentence (title/instructions/information) 
//---------------------------------------------------------------------------------------
void writeOnScreenLocation(Lines line_location, std::string sentence){
	Point* location = NULL;

	switch (line_location)
	{
	case LINE_ONE_RIGHT:{
		location = new Point(40,0);

		break;
	}
	case LINE_ONE_LEFT:{
		location = new Point(0, 0);

		break;
	}
	case LINE_TWO_LEFT:{
		location = new Point(0, 1);

		break;
	}
	case LINE_TWO_RIGHT:{
		location = new Point(40, 1);

		break;
	}
	case LINE_THREE_LEFT:{
		location = new Point(0, 2);

		break;
	}
	case LINE_THREE_RIGHT:{
		location = new Point(40, 2);

		break;
	}
	case LINE_ONE_MIDDLE:{
		location = new Point(20, 0);

		break;
	}
	default:
		break;
	}

	gotoxy(*location);

	// Clean the title
	for (int i = location->getX(); i < (location->getX() + LENGH_OF_LINE / 2); i++)
	{
		cout << " ";
	}

	// print sentence
	gotoxy(*location);
	cout << sentence;

	// back to the screen game
	gotoxy(0, 3);
}


//---------------------------------------------------------------------------------------
// function overloading for gotoxy 
//---------------------------------------------------------------------------------------
void gotoxy(const Point& p){
	gotoxy(p.getX(), p.getY());
}

//---------------------------------------------------------------------------------------
// gets location where to print next cout (done already)
//---------------------------------------------------------------------------------------
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout<<flush;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}
// END OF NEW CODE EX1

//---------------------------------------------------------------------------------------
// set Text color (done already)
//---------------------------------------------------------------------------------------
void setTextColor(Color colorToSet){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}

//---------------------------------------------------------------------------------------
// hide Cursor (done already)
//---------------------------------------------------------------------------------------
void hideCursor()
{
	 HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	 CONSOLE_CURSOR_INFO CURSOR;
	 CURSOR.dwSize = 1;
	 CURSOR.bVisible = FALSE;
	 SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}

//---------------------------------------------------------------------------------------
// clear Screen (done already)
//---------------------------------------------------------------------------------------
void clear_screen()
{
	system("cls");
}

#endif


