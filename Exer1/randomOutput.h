//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// RandomOutput.h
// -----------
// This file declares a
//
// Author: Roi Fogler && Motty Katz 
// First version: 2015-03-23
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

#ifndef _RANDOMOUTPUT_H
#define _RANDOMOUTPUT_H

#include <iostream>
#include "ScreenData.h"
#include "Sign.h"
#include "Point.h"
#include "io_utils.h"

using namespace std;

class RandomOutput
{
	static const int START_RANDOM_NUMBER = 1;
	static Point randomPoint(unsigned int range_to, unsigned int range_from = START_RANDOM_NUMBER) { return Point(CreateRandomValue(range_to), CreateRandomValue(range_from)); }
	static bool RandomOutput::isPointNearOrInsideOtherPoint(ScreenData* sData, Point* p);
public:
	

	// Methods
	static int CreateRandomValue(ScreenData* sData, unsigned int range_to, unsigned int range_from = START_RANDOM_NUMBER);
	static int CreateRandomValue(unsigned int range_to, unsigned int range_from = START_RANDOM_NUMBER);
	static Sign::Operator CreateRandomSign();
	static Point randomPointInScreen(ScreenData* sData);
};

#endif