//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Direction.cpp
// -----------
// This file responsible for the directiom
//
// Author: Motty Katz  && Roi Fogler
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Direction.h"

//---------------------------------------------------------------------------------------
// this function get opposite direction
//---------------------------------------------------------------------------------------
Direction::value Direction::getOppositeDirection(value d){
	if (d == UP){
		return DOWN;
	}
	else if (d == DOWN){
		return UP;
	}
	else if (d == RIGHT){
		return LEFT;
	}
	else if (d == LEFT){
		return RIGHT;
	}
	else{
		return STAY;
	}
}

//---------------------------------------------------------------------------------------
// this function get orthogonal direction
//---------------------------------------------------------------------------------------
Direction::value Direction::getOrthogonalDirection(value d){
	if (d == UP || d == DOWN){
		return RIGHT;
	}
	else if (d == RIGHT || d == LEFT){
		return UP;
	}
	else{
		return STAY;
	}
}