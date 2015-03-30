
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Point.cpp
// -----------
// This file 
//
// Author: Motty Katz  && Roi Fogler
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// In the file itself, add above each change/addition a remark saying: "NEW CODE EX1, author=<name>, date=<YYYY-MM-DD>"
// and close it at the end with a remark saying "END of NEW CODE EX1" 
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "Player.h"

Player::Player(Player::numberOfPlayer number, Direction::value d) :playerNumber(number), direction(d){
	// Check which player is that and init
	if (playerNumber == Player::One){
		setLocationPoint(PLAYER_1_X_POSITION, PLAYER_1_Y_POSITION); //new Point(PLAYER_1_X_POSITION, PLAYER_1_Y_POSITION);
	}
	else if (playerNumber == Player::Two){
		setLocationPoint(PLAYER_2_X_POSITION, PLAYER_2_Y_POSITION); //locationPoint = new Point(PLAYER_2_X_POSITION, PLAYER_2_Y_POSITION);
	}

	// Move by inited directions
	move(getDirection());
}

void Player::setLocationPoint(const Point& point){
	locationPoint = new Point(point.getX(), point.getY());
}

void Player::setLocationPoint(unsigned int x, unsigned int y){
	locationPoint = new Point(x, y);
}

void Player::move(Direction::value direction){
	Point* targetPoint = NULL; // using a pointer to avoid wasting of memory
	
	// Delete last location
	gotoxy(getLocationPoint());
	cout << " ";

	// Init new direction
	setDirection(direction);
	
	// Take care all opptional directions
	switch (direction)
	{
		case Direction::DOWN:{
			targetPoint = new Point(getLocationPoint().getX(), getLocationPoint().getY() + 1);

			break;
		}
		case Direction::UP:{
			targetPoint = new Point(getLocationPoint().getX(), getLocationPoint().getY() - 1);

			break;
		}
		case Direction::RIGHT:{
			targetPoint = new Point(getLocationPoint().getX() + 1, getLocationPoint().getY());

			break;
		}
		case Direction::LEFT:{
			targetPoint = new Point(getLocationPoint().getX() - 1, getLocationPoint().getY());

			break;
		}
		default:{ // STAY

			break;
		}
	}

	// Case it was not STAY
	if (targetPoint != NULL){
		// set new location: take care that screen size is (24 X 80)
		setLocationPoint(targetPoint->getX() % LENGH_OF_LINE,
			(targetPoint->getY() % LENGH_OF_PAGE) +
			AMOUNT_OF_INSTRUCTIONS_LINE);
	}	

	// Print new location
	printSighn();
}