//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// NumEaters.cpp
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

#include "NumEaters.h"

//---------------------------------------------------------------------------------------
// ctor
//---------------------------------------------------------------------------------------
NumEaters::NumEaters(const Point& p, const Point& p1, const Point& p2, Direction::value d) : Creature(p, d), targetLocPoint(locationPoint), pPlayer1Loc(p1), pPlayer2Loc(p2){
	// calc trace
	//move();
}


//---------------------------------------------------------------------------------------
// this method prints the sign
//---------------------------------------------------------------------------------------
void NumEaters::printSighn(){
	gotoxy(getLocationPoint());
	cout << NUM_EATERS_SIGN;
}

//---------------------------------------------------------------------------------------
// this method set next loc point
//---------------------------------------------------------------------------------------
//void NumEaters::setNextLocPoint(const Point& p){
//	nextLocPoint = p;
//}

//---------------------------------------------------------------------------------------
// this method set next loc point
//---------------------------------------------------------------------------------------
//void NumEaters::setNextLocPoint(unsigned int x, unsigned int y){
//	setNextLocPoint(Point(x, y));
//}
//---------------------------------------------------------------------------------------
// this method set target loc point
//---------------------------------------------------------------------------------------
void NumEaters::setTargetLocPoint(const Point& p){
	targetLocPoint = p;
}

//---------------------------------------------------------------------------------------
// this method set target loc point
//---------------------------------------------------------------------------------------
void NumEaters::setTargetLocPoint(Point* p){
	if (p != NULL){
		Point pTemp = Point(p->getX(), p->getY());
		//delete p;
		targetLocPoint = pTemp;
	}
}

//---------------------------------------------------------------------------------------
// this method is virtual move
//---------------------------------------------------------------------------------------
void NumEaters::move(int currIteration){

	//if (getTargetLocPoint() != NULL){
		if (getTargetLocPoint().getX() > getLocationPoint().getX()){
			setDirection(Direction::RIGHT);
			//setNextLocPoint(getLocationPoint().getX() + 1, getLocationPoint().getY());
		}
		else if (getTargetLocPoint().getX() < getLocationPoint().getX()){
			setDirection(Direction::LEFT);
			//setNextLocPoint(getLocationPoint().getX() - 1, getLocationPoint().getY());
		}
		else if (getTargetLocPoint().getY() > getLocationPoint().getY()){
			setDirection(Direction::DOWN);
			//setNextLocPoint(getLocationPoint().getX(), getLocationPoint().getY() + 1);
		}
		else if (getTargetLocPoint().getY() < getLocationPoint().getY()){
			setDirection(Direction::UP);
			//setNextLocPoint(getLocationPoint().getX(), getLocationPoint().getY() - 1);
		}

		if (getNextLocation() == getPlayer1LocPoint() ||
			getNextLocation() == getPlayer2LocPoint()){
			setDirection(Direction::getOppositeDirection(getDirection()));
		}
		
		Creature::move(currIteration);
	//}
}