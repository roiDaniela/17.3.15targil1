//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Shoot.cpp
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

#include "Shoot.h"

//---------------------------------------------------------------------------------------
// this method moves the point
//---------------------------------------------------------------------------------------
void Shoot::move(){
	Point targetPoint = getLocationPoint();
	
	// Delete last location
	CleanScreenAtPoint(targetPoint);

	calcShootTargetPoint(targetPoint);

	// set new location 
	setLocationPoint(targetPoint);

	// Print new location
	printSighn();
}

//---------------------------------------------------------------------------------------
// ctor
//---------------------------------------------------------------------------------------
Shoot::Shoot(Direction::value d, const Point& p) : direction(d),
   												   locationPoint(p){
	move();
}

//---------------------------------------------------------------------------------------
// this method calculate the next location
//---------------------------------------------------------------------------------------
void Shoot::calcShootTargetPoint(Point& targetPoint){
	// Take care all opptional directions
	if (targetPoint != getLocationPoint()){
		targetPoint = getLocationPoint();
	}

	// screen is 24X80 needs to be cyclic
	switch (Shoot::getDirection())
	{
		case Direction::DOWN:{
			if (targetPoint.getY() + 1 > LENGH_OF_PAGE){
				targetPoint.setY(((targetPoint.getY() + 1) % LENGH_OF_PAGE) + AMOUNT_OF_INSTRUCTIONS_LINE);
			}
			else{
				targetPoint.setY(targetPoint.getY() + 1);
			}
			break;
		}
		case Direction::UP:{
			if (targetPoint.getY() - 1 <= AMOUNT_OF_INSTRUCTIONS_LINE){
				targetPoint.setY(LENGH_OF_PAGE - (targetPoint.getY() % AMOUNT_OF_INSTRUCTIONS_LINE));
			}
			else{
				targetPoint.setY(getLocationPoint().getY() - 1);
			}

			break;
		}
		case Direction::RIGHT:{
			targetPoint.setX((getLocationPoint().getX() + 1) % LENGH_OF_LINE);

			break;
		}
		case Direction::LEFT:{
			if (getLocationPoint().getX() - 1 == -1){
				targetPoint.setX(LENGH_OF_LINE - 1);
			}
			else{
				targetPoint.setX(getLocationPoint().getX() - 1);
			}
		
			break;
		}
		default:{ // STAY

			break;
		}
	}
}
void Shoot::Stop(){
	setDirection(Direction::STAY);
	CleanScreenAtPoint(getLocationPoint());
}

//---------------------------------------------------------------------------------------
// this method prints the sign
//---------------------------------------------------------------------------------------
void Shoot::printSighn(){
	gotoxy(getLocationPoint());
	cout << Shoot::SHOOT_SIGN;
}

//---------------------------------------------------------------------------------------
// this method gets the new direction and returns what should be the next location of
//---------------------------------------------------------------------------------------
Point Shoot::getNextLocation(){
	Point targetPoint = getLocationPoint();

	calcShootTargetPoint(targetPoint);

	return targetPoint;
}
