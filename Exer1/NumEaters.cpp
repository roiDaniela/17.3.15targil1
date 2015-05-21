//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// NumEaters.cpp
// -----------
// This file
//
// Author: Motty Katz  && Roi Fogler
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "NumEaters.h"

//---------------------------------------------------------------------------------------
// ctor
//---------------------------------------------------------------------------------------
NumEaters::NumEaters(const Point& p, Direction::value d) : Creature(p, d){
	// calc trace
	//move();
}


//---------------------------------------------------------------------------------------
// this method prints the sign
//---------------------------------------------------------------------------------------
void NumEaters::printSighn(){
	gotoxy(getLocationPoint());
	cout << NUM_EATERS_SIGN;
}
