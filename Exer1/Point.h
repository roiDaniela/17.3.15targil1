//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Point.h
// -----------
// This file responsible for the new type: Point. this type is neccessery beacuse we want to respresnt location
// of the values\players on the screen
//
// Author: Roi Fogler && Motty Katz 
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _POINT_H
#define _POINT_H

#include<iostream>

using namespace std;

class Point
{
private:	
	int x,y; 
public:
	//Ctor
	Point(int x, int y) { this->x = x; this->y = y; }
	
	//enum PointData{ X_MAX_RANGE = 80, Y_MAX_RANGE = 24, X_MIN_RANGE = 0, Y_MIN_RANGE = 3 };
	
	// Getter & setter
	int getX() const { return x; };
	void setX(int x){ this->x = x; };
	int getY() const { return y; };
	void setY(int y){ this->y = y; };
	bool IsPointsAdjacent(const Point& pointToCompare) ;
	int calcDistance(const Point&, int, int) const;

	//Operator Overloding
	inline bool operator<(const Point& p)const{ 
		if (y < p.getY()) return true; 
		else if ((y == p.getY()) && x < p.getX()) return true;
		return false;
	}

	bool operator==(const Point& p)const { return ((p.x == this->x) && (p.y == this->y)); };
	bool operator!=(const Point& p)const { return !operator==(p); }
	Point operator-(const Point& p)const { return (Point((p.x - this->x), (p.y - this->y))); };
};

#endif