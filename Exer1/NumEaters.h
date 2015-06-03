//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// NumEaters.h
// -----------
// This file is the creature num eaters 
//
// Author: Roi Fogler && Motty Katz 
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _NUMEATERS_H
#define _NUMEATERS_H

#include "Creature.h"
#include "Player.h"

using namespace std;

class NumEaters : public Creature
{
private:
	// Private DM
	Point targetLocPoint;
	bool  isAlive;

public:
	static const int NUMEATER_1_X_POSITION = 10;
	static const int NUMEATER_1_Y_POSITION = 19;
	static const int NUMEATER_2_X_POSITION = 70;
	static const int NUMEATER_2_Y_POSITION = 19;
	static const char NUM_EATERS_SIGN = '%';

	// Getter && Setter
	Point getTargetLocPoint(){ return targetLocPoint; }
	void setTargetLocPoint(const Point& p);
	bool getIsAlive(){ return isAlive; }
	void setIsAlive(bool isA){ isAlive = isA; }

	void calcNumEaterDirection(bool nIsUp = false, 
		                       bool bIsDown = false, 
							   bool bIsRight = false, 
							   bool bIsLeft = false);
	
	// ctor
	NumEaters(const Point& p, Direction::value d);

	// Methods
	virtual void printSighn();
};
#endif