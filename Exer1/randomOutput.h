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

using namespace std;

class RandomOutput
{
	
public:
	

	// Methods
	static int CreateRandomValue(ScreenData* sData, unsigned int range_from, unsigned int range_to);
	static int CreateRandomValue(unsigned int range_from, unsigned int range_to);
	static Sign::Operator CreateRandomSign();
};

#endif