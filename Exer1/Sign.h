//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Direction.h
// -----------
// This file declares a class with an enum for the possible signs
//
// Author: Motty Katz && Roi Fogler
// First version: 2015-03-18
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _SIGN_H_
#define _SIGN_H_

class Sign
{
public:
	enum Operator
	{
			MINUS = 0xFFFF,
			PLUS,
			MULT,
			DIV
	};
};

#endif