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
// this method calc the next step
//---------------------------------------------------------------------------------------
Point Creature::nextStep(Direction::value d) const{
	Point tmp(getLocationPoint());
	switch (d)
	{
	case Direction::DOWN:{
		/*if (tmp.getY() + 1 > LENGH_OF_PAGE){
			tmp.setY(((tmp.getY() + 1) % LENGH_OF_PAGE) + AMOUNT_OF_INSTRUCTIONS_LINE - 1);
		}
		else{*/
			tmp.setY(tmp.getY() + 1);
		/*}*/

		break;
	}
	case Direction::UP:{
		/*if (tmp.getY() - 1 <= AMOUNT_OF_INSTRUCTIONS_LINE){
			tmp.setY(LENGH_OF_PAGE - (tmp.getY() % AMOUNT_OF_INSTRUCTIONS_LINE));
		}
		else{*/
			tmp.setY(tmp.getY() - 1);
		/*}*/

		break;
	}
	case Direction::RIGHT:{
		tmp.setX((tmp.getX() + 1) % LENGH_OF_LINE);

		break;
	}
	case Direction::LEFT:{
		/*if (tmp.getX() - 1 == -1){
			tmp.setX(LENGH_OF_LINE - 1);
		}
		else{*/
			tmp.setX(tmp.getX() - 1);
		/*}*/

		break;
	}
	default:{ // STAY

		break;
	}
	}

	tmp.fixPointToScreenSize();
	return tmp;
}
//---------------------------------------------------------------------------------------
// this method calculate the next location by the direction
//---------------------------------------------------------------------------------------
void Creature::calcTargetPoint(Point& targetPoint) const{

	// Take care all opptional directions
	Direction::value d = getDirection();
	// screen is 24X80 needs to be cyclic
	targetPoint = nextStep(d);
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
