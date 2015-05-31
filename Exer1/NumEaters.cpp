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
NumEaters::NumEaters(const Point& p, Direction::value d) : Creature(p, d), targetLocPoint(locationPoint)/*, pPlayer1Loc(p1), pPlayer2Loc(p2)*/{
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
// this method calculate the numEater Direction
//---------------------------------------------------------------------------------------
void NumEaters::calcNumEaterDirection(Player pl1, Player pl2, Creature c){
	Point p1 = getTargetLocPoint();
	Point p2 = getLocationPoint();

	// Set direction
	if (getTargetLocPoint() == getLocationPoint()){
		setDirection(Direction::STAY);
	}
	else if (((getTargetLocPoint().getX() > getLocationPoint().getX()) &&
		(abs(getTargetLocPoint().getX() - getLocationPoint().getX()) < LENGH_OF_LINE / 2)) ||
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
		abs(getTargetLocPoint().getY() - getLocationPoint().getY()) < LENGH_OF_PAGE / 2) ||
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

	Point p3 = getNextLocation();
	Point p4 = pl1.getNextLocation();
	Point p5 = pl1.getNextNextLocation();

	// Avoid crashes with players and other eater
	if ((pl1.getLocationPoint() == getNextLocation() ||
		pl1.getNextLocation() == getNextLocation() ||
		pl1.getNextNextLocation() == getNextLocation() ||
		pl1.getLocationPoint() == getLocationPoint() ||
		pl1.getNextLocation() == getLocationPoint() ||
		pl1.getNextNextLocation() == getLocationPoint()) &&
		(pl2.getLocationPoint() == getNextLocation() ||
		pl2.getNextLocation() == getNextLocation() ||
		pl2.getNextNextLocation() == getNextLocation() ||
		pl2.getLocationPoint() == getLocationPoint() ||
		pl2.getNextLocation() == getLocationPoint() ||
		pl2.getNextNextLocation() == getLocationPoint())){
			setDirection(Direction::getOrthogonalDirection(getDirection()));
	}
	else if (pl1.getLocationPoint() == getNextLocation() ||
		pl1.getNextLocation() == getNextLocation() ||
		pl1.getNextNextLocation() == getNextLocation() ||
		pl1.getLocationPoint() == getLocationPoint() ||
		pl1.getNextLocation() == getLocationPoint() ||
		pl1.getNextNextLocation() == getLocationPoint()){
			setDirection(Direction::getOppositeDirection(getDirection()));
	}
	else if (pl2.getLocationPoint() == getNextLocation() ||
		     pl2.getNextLocation() == getNextLocation() ||
			 pl2.getNextNextLocation() == getNextLocation() ||
			 pl2.getLocationPoint() == getLocationPoint() ||
			 pl2.getNextLocation() == getLocationPoint() ||
			 pl2.getNextNextLocation() == getLocationPoint()){
				setDirection(Direction::getOppositeDirection(getDirection()));
	}
	else if (c.getLocationPoint() == getNextLocation() ||
		     c.getNextLocation() == getNextLocation() ||
			 c.getLocationPoint() == getLocationPoint() ||
			 c.getNextLocation() == getLocationPoint()){
				setDirection(c.getDirection());
	}
}

//---------------------------------------------------------------------------------------
// this method is virtual move
//---------------------------------------------------------------------------------------
void NumEaters::move(int currIteration){
	Creature::move(currIteration);
}