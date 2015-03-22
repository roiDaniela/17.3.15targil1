//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Point.h
// -----------
// This file declares a class of point
//
// Author: Roi Fogler && Motty Katz 
// First version: 2015-03-22
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

#ifndef _POINT_H
#define _POINT_H

#include<iostream>
using namespace std;

class Point
{
private:	
	unsigned int x,y; 
public:
	//Ctor
	Point(unsigned int x, unsigned int y){ this->x = x; this->y = y; }
	
	// Getter & setter
	unsigned getX(){ return x; };
	void setX(unsigned int x){ this->x = x; };
	unsigned int getY(){ return y; };
	void setY(unsigned int y){ this->y = y; };

	// Methods
	Point randomPoint(unsigned target, unsigned int start = 1){ rand() % target + start; }

	//Operator Overloding
	inline bool operator==(const Point& p){return ((p.x == this->x) && (p.y == this->y)); };
	inline bool operator!=(const Point& p){ return !operator==(p); }
};

#endif