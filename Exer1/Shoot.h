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
public:
	enum ShootStatus
	{
		NOT_ALIVE,
		WORKING,
		STOPPED
	};

	enum MOVE_KEYS_SHOOT
	{
		PLAYER_1_SHOOT = 'z',
		PLAYER_2_SHOOT = 'n'
	};

private:
	// private DM
	Point locationPoint;
	Direction::value direction;
	ShootStatus status;

	// empty ctor
	//Shoot(); // cant use like that
	
public:

	static const char SHOOT_SIGN = '*';

	// Getter && Setter
	void setDirection(Direction::value d){ direction = d; }
	Direction::value getDirection() const{ return direction; }

	void setShootStatus(ShootStatus s){ status = s; }
	ShootStatus getShootStatus() const{ return status; }

	void setLocationPoint(const Point& p){ locationPoint = p; }
	void setLocationPoint(unsigned int x, unsigned int y){ 
		locationPoint.setX(x); 
		locationPoint.setY(y);
	}

	Point getLocationPoint() const{ return locationPoint; } 

	// ctor
	Shoot(Direction::value d, Point p) : direction(d), locationPoint(p), status(ShootStatus::WORKING) {
		move();
	}

	Shoot() : direction(Direction::STAY), locationPoint(Point(0,0)), status(ShootStatus::NOT_ALIVE) {}

	// Methods
	void Stop();
	void move();
	void printSighn(){
		gotoxy(getLocationPoint());
		cout << Shoot::SHOOT_SIGN;
	}
};
#endif