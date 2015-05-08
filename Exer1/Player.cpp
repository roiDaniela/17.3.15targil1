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

#include "Player.h"

//---------------------------------------------------------------------------------------
// Ctor
//---------------------------------------------------------------------------------------
Player::Player(Player::numberOfPlayer number, Direction::value d) : playerNumber(number),
																	direction(d),
																	winCounter(0),
																	shootCounter(5),
																	errorCounter(0),
																    locationPoint((number == Player::One) ? 
																	               Point(PLAYER_1_X_POSITION, PLAYER_1_Y_POSITION) : 
																				   Point(PLAYER_2_X_POSITION, PLAYER_2_Y_POSITION)){
	// Move by inited directions
	move(getDirection());
}

//---------------------------------------------------------------------------------------
// this method sets a new location to the curr player. gets point (function overloading)
//---------------------------------------------------------------------------------------
void Player::setLocationPoint(const Point& point){
	locationPoint = point;
}

//---------------------------------------------------------------------------------------
// this method sets a new location to the curr player. gets x,y (function overloading)
//---------------------------------------------------------------------------------------
void Player::setLocationPoint(unsigned int x, unsigned int y){
	locationPoint = Point(x, y);
}

//---------------------------------------------------------------------------------------
// this method calculate the next location by the direction
//---------------------------------------------------------------------------------------
void Player::calcTargetPoint(Point& targetPoint){
	
	// Take care all opptional directions
	switch (direction)
	{
	case Direction::DOWN:{
		targetPoint = Point(getLocationPoint().getX(), getLocationPoint().getY() + 1);

		break;
	}
	case Direction::UP:{
		targetPoint = Point(getLocationPoint().getX(), getLocationPoint().getY() - 1);

		break;
	}
	case Direction::RIGHT:{
		targetPoint = Point(getLocationPoint().getX() + 1, getLocationPoint().getY());

		break;
	}
	case Direction::LEFT:{
		targetPoint = Point(getLocationPoint().getX() - 1, getLocationPoint().getY());

		break;
	}
	default:{ // STAY

		break;
	}
	}

	// Case it was not STAY
	if (direction != Direction::STAY/*targetPoint != NULL*/){

		// Needs to be cyclic: take care that screen size is (24 X 80)
		if (getDirection() == Direction::RIGHT){
			targetPoint.setX(targetPoint.getX() % LENGH_OF_LINE);
		}
		else if (getDirection() == Direction::LEFT && targetPoint.getX() == -1){
			targetPoint.setX(LENGH_OF_LINE - 1);
		}


		if ((getDirection() == Direction::DOWN) && (targetPoint.getY() > LENGH_OF_PAGE)){
			targetPoint.setY((targetPoint.getY() % LENGH_OF_PAGE) + AMOUNT_OF_INSTRUCTIONS_LINE);
		}
		else if ((getDirection() == Direction::UP) && (targetPoint.getY() <= AMOUNT_OF_INSTRUCTIONS_LINE)){
			targetPoint.setY(LENGH_OF_PAGE - (targetPoint.getY() % AMOUNT_OF_INSTRUCTIONS_LINE));
		}
	}
}
//---------------------------------------------------------------------------------------
// this method gets direction and moves the player to the recived directions
//---------------------------------------------------------------------------------------
void Player::move(Direction::value direction){
	Point targetPoint = getLocationPoint(); 

	// Init new direction
	setDirection(direction);
	
	calcTargetPoint(targetPoint);

	// Delete last location
	gotoxy(getLocationPoint());
	cout << " ";

	// set new location 
	setLocationPoint(targetPoint);

	// Print new location
	printSighn();
}

//---------------------------------------------------------------------------------------
// this method gets the new direction and returns what should be the next location of
// curr player
//---------------------------------------------------------------------------------------
Point Player::getNextLocation(){
	Point targetPoint = getLocationPoint();

	calcTargetPoint(targetPoint);

	return targetPoint;
}

//---------------------------------------------------------------------------------------
// this method uses the player to shoot
//---------------------------------------------------------------------------------------
Shoot* Player::shoot(){
	if (shootCounter > 0){
		--shootCounter;
		return new Shoot(getDirection(), getNextLocation());
	}
	
	return NULL;
}

//---------------------------------------------------------------------------------------
// this method prints the player sign
//---------------------------------------------------------------------------------------
void Player::printSighn(){
	gotoxy(getLocationPoint());
	(playerNumber == One) ? cout << PLAYER_1_SIGN : cout << PLAYER_2_SIGN;
}