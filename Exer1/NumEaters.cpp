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
	if (((getTargetLocPoint().getX() > getLocationPoint().getX()) && 
	    (abs(getTargetLocPoint().getX() - getLocationPoint().getX()) < LENGH_OF_LINE/2)) ||
		(getTargetLocPoint().getX() < getLocationPoint().getX() && 
		(abs(getTargetLocPoint().getX() - getLocationPoint().getX()) > LENGH_OF_LINE / 2))){
		setDirection(Direction::RIGHT);
	}
	else if (((getTargetLocPoint().getX() < getLocationPoint().getX()) && 
		     (abs(getTargetLocPoint().getX() - getLocationPoint().getX()) < LENGH_OF_LINE / 2)) || 
			 ((getTargetLocPoint().getX() > getLocationPoint().getX()) && 
			 (abs(getTargetLocPoint().getX() - getLocationPoint().getX()) > LENGH_OF_LINE / 2))){
		setDirection(Direction::LEFT);
	}
	else if ((getTargetLocPoint().getY() > getLocationPoint().getY() &&
		     abs(getTargetLocPoint().getY() - getLocationPoint().getY()) < LENGH_OF_PAGE/2) ||
			 (getTargetLocPoint().getY() < getLocationPoint().getY() &&
			 abs(getTargetLocPoint().getY() - getLocationPoint().getY()) > LENGH_OF_PAGE / 2)){
		setDirection(Direction::DOWN);
	}
	else if (((getTargetLocPoint().getY() < getLocationPoint().getY()) && 
		     (abs(getTargetLocPoint().getY() - getLocationPoint().getY()) < LENGH_OF_PAGE / 2)) || 
			 ((getTargetLocPoint().getY() > getLocationPoint().getY()) &&
			 (abs(getTargetLocPoint().getY() - getLocationPoint().getY()) > LENGH_OF_PAGE / 2))){
		setDirection(Direction::UP);
	}

	if (getNextLocation() == getPlayer1LocPoint() ||
		getNextLocation() == getPlayer2LocPoint()){
		setDirection(Direction::getOppositeDirection(getDirection()));
	}
		
	Creature::move(currIteration);
}