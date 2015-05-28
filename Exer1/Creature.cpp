//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Player.cpp
// -----------
// This file is responsible to the new type = player: players in the game. here we set the players locations. signs and moves
// All the data on the players should be on this member.
//
// Author: Motty Katz  && Roi Fogler
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "Creature.h"

//---------------------------------------------------------------------------------------
// this method sets a new location to the curr player. gets point (function overloading)
//---------------------------------------------------------------------------------------
void Creature::setLocationPoint(const Point& point){
	locationPoint = point;
}

//---------------------------------------------------------------------------------------
// this method sets a new location to the curr player. gets x,y (function overloading)
//---------------------------------------------------------------------------------------
void Creature::setLocationPoint(unsigned int x, unsigned int y){
	locationPoint = Point(x, y);
}

//---------------------------------------------------------------------------------------
// this method calculate the next location by the direction
//---------------------------------------------------------------------------------------
void Creature::calcTargetPoint(Point& targetPoint) const{

	// Take care all opptional directions
	//if (targetPoint != getLocationPoint()){
	//	targetPoint = getLocationPoint();
	//}
	Direction::value d = getDirection();
	// screen is 24X80 needs to be cyclic
	switch (getDirection())
	{
	case Direction::DOWN:{
		if (targetPoint.getY() + 1 > LENGH_OF_PAGE){
			targetPoint.setY(((targetPoint.getY() + 1) % LENGH_OF_PAGE) + AMOUNT_OF_INSTRUCTIONS_LINE - 1);
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
			targetPoint.setY(targetPoint.getY() - 1);
		}

		break;
	}
	case Direction::RIGHT:{
		targetPoint.setX((targetPoint.getX() + 1) % LENGH_OF_LINE);

		break;
	}
	case Direction::LEFT:{
		if (targetPoint.getX() - 1 == -1){
			targetPoint.setX(LENGH_OF_LINE - 1);
		}
		else{
			targetPoint.setX(targetPoint.getX() - 1);
		}

		break;
	}
	default:{ // STAY

		break;
	}
	}
}
//---------------------------------------------------------------------------------------
// this method gets direction and moves the player to the recived directions
//---------------------------------------------------------------------------------------
void Creature::move(int currentIteration){
	setLastMoveIteration(currentIteration);

	Point targetPoint = getLocationPoint();

	// Init new direction
	//setDirection(getDirection());

	calcTargetPoint(targetPoint);

	// Delete last location
	CleanScreenAtPoint(getLocationPoint());

	// set new location 
	setLocationPoint(targetPoint);

	// Print new location
	printSighn();
}

//---------------------------------------------------------------------------------------
// this method gets the new direction and returns what should be the next location of
// curr player
//---------------------------------------------------------------------------------------
Point Creature::getNextLocation() const{
	Point targetPoint = getLocationPoint();

	calcTargetPoint(targetPoint);

	return targetPoint;
}
