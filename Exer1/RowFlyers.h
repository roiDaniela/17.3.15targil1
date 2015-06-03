//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// RowFlyers.h
// -----------
// This file is the creature row Flyers
//
// Author: Roi Fogler && Motty Katz 
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _ROWFLYERS_H
#define _ROWFLYERS_H

#include "Creature.h"

using namespace std;

class RowFlyers : public Creature
{
private:

public:
	static const int ROWFLYERS_1_X_POSITION = 30;
	static const int ROWFLYERS_1_Y_POSITION = 23;
	static const int ROWFLYERS_2_X_POSITION = 50;
	static const int ROWFLYERS_2_Y_POSITION = 15;
	static const char ROWFLYERS_SIGN = '!';

	// Getter && Setter

	// ctor
	RowFlyers(const Point& p, Direction::value d) :Creature(p, d){}

	// Methods
	virtual void printSighn(){ 
		gotoxy(getLocationPoint()); 
		cout << ROWFLYERS_SIGN;
	}
};
#endif