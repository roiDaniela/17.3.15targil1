//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Shoot.h
// -----------
// This file 
//
// Author: Roi Fogler && Motty Katz 
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _SHOOT_H
#define _SHOOT_H

#include "Creature.h"

using namespace std;

class Shoot: public Creature
{
private:
	// private DM
	
public:
	static const int SHOOT_AMOUNT_MIN_SIZE = 5;
	static const char SHOOT_SIGN = '*';

	// Getter && Setter

	// ctor
	Shoot(Direction::value d, const Point& p, int currIteration);

	// Methods
	virtual void printSighn();
};
#endif