//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// RandomOutput.h
// -----------
// This file represents the random output (numbers, points, signs) in the game
//
// Author: Roi Fogler && Motty Katz 
// First version: 2015-03-23
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _RANDOMOUTPUT_H
#define _RANDOMOUTPUT_H

#include <iostream>
#include "ScreenData.h"
#include "Sign.h"
#include "Point.h"
#include "io_utils.h"
#include <time.h>


using namespace std;

class RandomOutput
{
	static const int START_RANDOM_NUMBER = 1;
	static const int FROM_X_POINT_NUMBER = 0;
	static const int FROM_Y_POINT_NUMBER = 4;
	static const int TO_X_POINT_NUMBER = 80;
	static const int TO_Y_POINT_NUMBER = 24;

public:

	// Methods
	static unsigned int CreateRandomValue(ScreenData* sData, unsigned int range_to, unsigned int range_from = START_RANDOM_NUMBER);
	static unsigned int CreateRandomValue(unsigned int range_to, unsigned int range_from = START_RANDOM_NUMBER);
	static Sign::Operator CreateRandomSign();
	static Point* CreateRandomPoint(ScreenData& sData, int numOfDigits);
	
	//---------------------------------------------------------------------------------------
	// this function creates a random point
	//---------------------------------------------------------------------------------------
	static Point CreateRandomPoint() {
		return Point(CreateRandomValue(TO_X_POINT_NUMBER, FROM_X_POINT_NUMBER),
			CreateRandomValue(TO_Y_POINT_NUMBER, FROM_Y_POINT_NUMBER));
	}
};

#endif