//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// NumEaters.h
// -----------
// This file is the creature num eaters 
//
// Author: Roi Fogler && Motty Katz 
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _NUMEATERS_H
#define _NUMEATERS_H

#include "Creature.h"

using namespace std;

class NumEaters : public Creature
{
private:

public:
	static const int NUMEATER_1_X_POSITION = 10;
	static const int NUMEATER_1_Y_POSITION = 19;
	static const int NUMEATER_2_X_POSITION = 70;
	static const int NUMEATER_2_Y_POSITION = 19;
	static const char NUM_EATERS_SIGN = '%';

	// Getter && Setter

	// ctor
	NumEaters(const Point& p, Direction::value d);

	// Methods
	void printSighn();
};
#endif