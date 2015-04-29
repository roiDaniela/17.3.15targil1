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
																	errorCounter(0),
																	isWin_1(false),
																	isWin_2(false),
																    locationPoint((number == Player::One) ? 
																	               Point(PLAYER_1_X_POSITION, PLAYER_1_Y_POSITION) : 
																				   Point(PLAYER_2_X_POSITION, PLAYER_2_Y_POSITION)){
	// init first shoots
	for (int i = 0; i < Shoot::SHOOT_ARRAY_MIN_SIZE; i++)
	{
		arrayOfShoot[i].setLocationPoint(locationPoint);
		arrayOfShoot[i].setShootStatus(Shoot::ShootStatus::READY);
	}

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
// this method returns the amount of player's shoot
//---------------------------------------------------------------------------------------
int Player::getNumberOfShoots(){
	int sizeCounter = 0;
	for (int i = 0; i < Shoot::SHOOT_ARRAY_MAX_SIZE; i++)
	{
		if (arrayOfShoot[i].getShootStatus() == Shoot::ShootStatus::READY){
			++sizeCounter;
		}
	}

	return sizeCounter;
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
// this method gets boolean represents if the counter initlzed and updated the counter
//---------------------------------------------------------------------------------------
void Player::updateWinCounter(bool isInitCounter){
	// Update counter
	if (getPlayerNumber() == One && getIsWin() && !isInitCounter){
		Player::winCounter_1++;
	}
	else if (getPlayerNumber() == Two && getIsWin() && !isInitCounter){
		Player::winCounter_2++;
	}

	// initlized
	if (isInitCounter){
		Player::winCounter_1 = 0;
		Player::winCounter_2 = 0;
	}
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

void Player::shoot(){
	for (int i = 0; i < Shoot::SHOOT_ARRAY_MAX_SIZE; i++)
	{
		if (arrayOfShoot[i].getShootStatus() == Shoot::ShootStatus::READY){
			arrayOfShoot[i].setDirection(direction);
			arrayOfShoot[i].setLocationPoint(getNextLocation());
			arrayOfShoot[i].setShootStatus(Shoot::ShootStatus::WORKING);
		}
	}
}

void Player::updateShootArray(int iterationCounter){
	// set the array lengh
	for (int i = 0; i < (iterationCounter / 200); i++)
	{
		if (arrayOfShoot[Shoot::SHOOT_ARRAY_MIN_SIZE + i].getShootStatus() == Shoot::ShootStatus::NOT_ALIVE){
			arrayOfShoot[Shoot::SHOOT_ARRAY_MIN_SIZE + i].setShootStatus(Shoot::ShootStatus::READY);
		}
	}
}

void Player::movePlayerShoots(){
	for (int i = 0; i < Shoot::SHOOT_ARRAY_MAX_SIZE; i++)
	{
		if (arrayOfShoot[i].getShootStatus() == Shoot::ShootStatus::WORKING){
			arrayOfShoot[i].move();
		}
	}
}