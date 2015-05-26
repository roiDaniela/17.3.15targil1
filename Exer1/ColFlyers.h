//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ColFlyers.h
// -----------
// This file is the creature num eaters 
//
// Author: Roi Fogler && Motty Katz 
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _COLFLYERS_H
#define _COLFLYERS_H

#include "Creature.h"

using namespace std;

class ColFlyers : public Creature
{
private:

public:
	static const int COLFLYERS_1_X_POSITION = 45;
	static const int COLFLYERS_1_Y_POSITION = 23;
	static const int COLFLYERS_2_X_POSITION = 55;
	static const int COLFLYERS_2_Y_POSITION = 15;
	static const char COLFLYERS_SIGN = '$';

	// Getter && Setter

	// ctor
	ColFlyers(const Point& p, Direction::value d) :Creature(p, d){}

	// Methods
	virtual void move(int currIteration){
		if (lastMoveIteration != currIteration){
			Creature::move(currIteration);
		}
	}

	virtual void printSighn(){
		gotoxy(getLocationPoint());
		cout << COLFLYERS_SIGN;
	}
};
#endif