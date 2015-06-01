//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Point.cpp
// -----------
// This file responsible for the new type: Point. this type is neccessery beacuse we want to respresnt location
// of the values\players on the screen
//
// Author: Motty Katz  && Roi Fogler
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "Point.h"
#include <math.h>

//---------------------------------------------------------------------------------------
// this method gets a point to comapre and checks if curr point adjacent 
// the recived point
//---------------------------------------------------------------------------------------
bool Point::IsPointsAdjacent(const Point& pointToCompare) {
	return ( abs((*this - pointToCompare).getX() + (*this - pointToCompare).getY()) == 1 );
}

//---------------------------------------------------------------------------------------
// this function checks if the value is a creature
//---------------------------------------------------------------------------------------
int Point::calcDistance(const Point& ptLocation, int max_x_size, int max_y_size) const{
	int tmp = 0;
	if (abs(getX() - ptLocation.getX()) > max_x_size / 2){
		tmp += (getX() + ptLocation.getX()) % max_x_size;
	}
	else{
		tmp += abs(getX() - ptLocation.getX());
	}

	if (abs(getY() - ptLocation.getY()) > max_y_size / 2){
		tmp += (getY() + ptLocation.getY()) % max_y_size;
	}
	else{
		tmp += abs(getY() - ptLocation.getY());
	}

	return tmp;
}
