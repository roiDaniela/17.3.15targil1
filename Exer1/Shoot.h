//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Shoot.h
// -----------
// This file 
//
// Author: Roi Fogler && Motty Katz 
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _SHOOT_H
#define _SHOOT_H

#include "Point.h"
#include "Direction.h"
#include "io_utils.h"

using namespace std;

class Shoot
{
private:
	// private DM
	Point locationPoint;
	Direction::value direction;

	// Private Methods
	void Shoot::calcShootTargetPoint(Point& targetPoint);
	// empty ctor
	Shoot(); // cant use like that
	
public:
	static const int SHOOT_AMOUNT_MIN_SIZE = 5;
	static const char SHOOT_SIGN = '*';

	// Getter && Setter
	void setDirection(Direction::value d){ direction = d; }
	Direction::value getDirection() const{ return direction; }

	void setLocationPoint(const Point& p){ locationPoint = p; }
	void setLocationPoint(unsigned int x, unsigned int y){ 
		locationPoint.setX(x); 
		locationPoint.setY(y);
	}

	Point getLocationPoint() const{ return locationPoint; } 
	Point getNextLocation();

	// ctor
	Shoot(Direction::value d, const Point& p) : direction(d), locationPoint(p){
		move();
	}

	// Methods
	void Stop();
	void move();
	void printSighn();
};
#endif