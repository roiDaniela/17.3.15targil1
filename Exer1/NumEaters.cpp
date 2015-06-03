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
// this method calculate the numEater Direction
//---------------------------------------------------------------------------------------
void NumEaters::calcNumEaterDirection(bool bIsUp, bool bIsDown, bool bIsRight, bool bIsLeft){
	bool bIsMovingToSomwwhere = false;
	
	// Set direction
	if (getTargetLocPoint() == getLocationPoint()){
		setDirection(Direction::STAY);
		bIsMovingToSomwwhere = true;
	}
	else if (!bIsRight &&
		(((getTargetLocPoint().getX() > getLocationPoint().getX()) &&
		(abs(getTargetLocPoint().getX() - getLocationPoint().getX()) <= LENGH_OF_LINE / 2)) ||
		(getTargetLocPoint().getX() < getLocationPoint().getX() &&
		(abs(getTargetLocPoint().getX() - getLocationPoint().getX()) > LENGH_OF_LINE / 2)))){
		setDirection(Direction::RIGHT);
		bIsMovingToSomwwhere = true;
	}
	else if (!bIsLeft &&
		(((getTargetLocPoint().getX() < getLocationPoint().getX()) &&
		(abs(getTargetLocPoint().getX() - getLocationPoint().getX()) <= LENGH_OF_LINE / 2)) ||
		((getTargetLocPoint().getX() > getLocationPoint().getX()) &&
		(abs(getTargetLocPoint().getX() - getLocationPoint().getX()) > LENGH_OF_LINE / 2)))){
		setDirection(Direction::LEFT);
		bIsMovingToSomwwhere = true;
	}
	else if (!bIsDown &&
		((getTargetLocPoint().getY() > getLocationPoint().getY() &&
		abs(getTargetLocPoint().getY() - getLocationPoint().getY()) <= LENGH_OF_PAGE / 2) ||
		(getTargetLocPoint().getY() < getLocationPoint().getY() &&
		abs(getTargetLocPoint().getY() - getLocationPoint().getY()) > LENGH_OF_PAGE / 2))){
		setDirection(Direction::DOWN);
		bIsMovingToSomwwhere = true;
	}
	else if (!bIsUp &&
		(((getTargetLocPoint().getY() < getLocationPoint().getY()) &&
		(abs(getTargetLocPoint().getY() - getLocationPoint().getY()) <= LENGH_OF_PAGE / 2)) ||
		((getTargetLocPoint().getY() > getLocationPoint().getY()) &&
		(abs(getTargetLocPoint().getY() - getLocationPoint().getY()) > LENGH_OF_PAGE / 2)))){
		setDirection(Direction::UP);
		bIsMovingToSomwwhere = true;
	}

	// If he has not changed his direction, change it althogh crash
	if (!bIsMovingToSomwwhere){
		calcNumEaterDirection();
	}
}