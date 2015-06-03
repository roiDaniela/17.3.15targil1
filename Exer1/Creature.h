//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Creature.h
// -----------
// This file is the base file for creatures in the screen.
//
// Author: Roi Fogler && Motty Katz 
// First version: 2015-05-19
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _CREATURE_H
#define _CREATURE_H

#include "Point.h"
#include "Direction.h"
#include "io_utils.h"
#include <typeinfo.h>

using namespace std;

class Creature
{
protected:
	// private DM
	Point locationPoint;
	int lastMoveIteration;
	Direction::value direction;
	char sign;

	// Private Methods
	void calcTargetPoint(Point& targetPoint) const;

	// Avoid this ctor
	Creature();
public:
	static const int INITIONAL_ITERATION_COUNTER = -1;
	// Ctor
	Creature(const Point& p, Direction::value d = Direction::STAY) :locationPoint(p), direction(d), lastMoveIteration(INITIONAL_ITERATION_COUNTER){}

	// dtor
	//virtual ~Creature(){}

	// Getter && Setter
	void setDirection(Direction::value d){ direction = d; }
	Direction::value getDirection() const { return direction; }

	void setLocationPoint(const Point&);
	void setLocationPoint(unsigned int x, unsigned int y);

	Point getLocationPoint() const { return locationPoint; }
	Point getNextLocation() const;
	
	int getLastMoveIteration(){ return lastMoveIteration; }
	void setLastMoveIteration(int currIteration){ lastMoveIteration = currIteration; }

	// Methods
	Point nextStep(Direction::value) const;
	virtual void printSighn(){};
	virtual void move(int currentIteration);
	virtual bool operator==(const Creature& c)const { return ((c.getLocationPoint() == this->getLocationPoint()) && (typeid(c) == typeid(*this))); };
};

#endif