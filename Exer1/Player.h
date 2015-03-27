//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Point.h
// -----------
// This file declares a class of point
//
// Author: Roi Fogler && Motty Katz 
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// In the file itself, add above each change/addition a remark saying: "NEW CODE EX1, author=<name>, date=<YYYY-MM-DD>"
// and close it at the end with a remark saying "END of NEW CODE EX1" 
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _PLAYER_H
#define _PLAYER_H

#include "Point.h"
#include "Direction.h"
#include "io_utils.h"

using namespace std;

class Player
{
private:
	enum numberOfPlayer
	{
		One = 1,
		Two
	};

	numberOfPlayer playerNumber;
	Direction direction;
	Point* locationPoint;

	static const int PLAYER_1_X_POSITION = 10;
	static const int PLAYER_1_Y_POSITION = 9;
	static const int PLAYER_2_X_POSITION = 70;
	static const int PLAYER_2_Y_POSITION = 9;
	static const char PLAYER_1_SIGN = '@';
	static const char PLAYER_2_SIGN = '#';
public:
	Player(unsigned int number);// { locationPoint = new Point(0, 0), playerNumber = numberOfPlayer(number); }
	void printSighn(){
		//int u = (locationPoint->getX());
		gotoxy(*locationPoint);
		//gotoxy(locationPoint->getX(), locationPoint->getY());
		(playerNumber == numberOfPlayer::One) ? cout << PLAYER_1_SIGN : cout << PLAYER_2_SIGN;
	}
	//setDirection
};

#endif