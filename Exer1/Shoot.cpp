//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Shoot.cpp
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

#include "Shoot.h"

//---------------------------------------------------------------------------------------
// ctor
//---------------------------------------------------------------------------------------
Shoot::Shoot(Direction::value d, const Point& p, int currIteration) : Creature(p,d){
	move(currIteration);
}


//---------------------------------------------------------------------------------------
// this method prints the sign
//---------------------------------------------------------------------------------------
void Shoot::printSighn(){
	gotoxy(getLocationPoint());
	cout << SHOOT_SIGN;
}
