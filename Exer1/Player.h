//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Point.h
// -----------
// This file declares a class of point
//
// Author: Roi Fogler && Motty Katz 
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

#ifndef _PLAYER_H
#define _PLAYER_H

#include "Point.h"
#include "Direction.h"
#include "io_utils.h"

using namespace std;

class Player
{
private:
	// DM
	Point* locationPoint;
	Direction::value direction;

	static const int PLAYER_1_X_POSITION = 10;
	static const int PLAYER_1_Y_POSITION = 9;
	static const int PLAYER_2_X_POSITION = 70;
	static const int PLAYER_2_Y_POSITION = 9;
	static const char PLAYER_1_SIGN = '@';
	static const char PLAYER_2_SIGN = '#';

	// This Ctor shoudn't be in use
	Player::Player(){ }
public:
	// Which player is that
	enum numberOfPlayer
	{
		One = 1,
		Two
	};

	// Ctor
	Player(numberOfPlayer number, Direction::value d = Direction::STAY);

	// Getter && Setter
	void setDirection(Direction::value d){ direction = d; }
	Direction::value getDirection(){ return direction; }

	void setLocationPoint(const Point&);
	void setLocationPoint(unsigned int x, unsigned int y);
	Point getLocationPoint(){ return *locationPoint; }

	// Methods
	void printSighn(){
		gotoxy(*locationPoint);
		(playerNumber == numberOfPlayer::One) ? cout << PLAYER_1_SIGN : cout << PLAYER_2_SIGN;
	}

	void Player::move(Direction::value direction);

private:
	numberOfPlayer playerNumber;

public:
	// Getter && Setter
	void SetPlayerNumber(numberOfPlayer playerNumber1) { playerNumber = playerNumber1; }
	numberOfPlayer getPlayerNumber(){ return playerNumber; }
};

#endif