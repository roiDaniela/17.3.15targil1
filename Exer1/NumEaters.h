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
	/*Point pPlayer1Loc;
	Point pPlayer2Loc;*/

public:
	static const int NUMEATER_1_X_POSITION = 10;
	static const int NUMEATER_1_Y_POSITION = 19;
	static const int NUMEATER_2_X_POSITION = 70;
	static const int NUMEATER_2_Y_POSITION = 19;
	static const char NUM_EATERS_SIGN = '%';

	// Getter && Setter
	Point getTargetLocPoint(){ return targetLocPoint; }
	void setTargetLocPoint(const Point& p);
	//void setTargetLocPoint(Point* p);
	bool getIsAlive(){ return isAlive; }
	void setIsAlive(bool isA){ isAlive = isA; }

	void calcNumEaterDirection(Player, Player/*, NumEaters&*/);

	/*Point getPlayer1LocPoint(){ return pPlayer1Loc; }
	void setPlayer1LocPoint(const Point& p){ pPlayer1Loc = p; }

	Point getPlayer2LocPoint(){ return pPlayer2Loc; }
	void setPlayer2LocPoint(const Point& p){ pPlayer2Loc = p; }*/
	
	// ctor
	NumEaters(const Point& p, Direction::value d);

	// dtor
	//virtual ~NumEaters(){
	//	delete targetLocPoint;
	//	delete nextLocPoint;
	//}

	// Methods
	virtual void printSighn();
	virtual void move(int currIteration);
};
#endif