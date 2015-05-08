//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Player.h
// -----------
// This file is responsible to the new type = player: players in the game. here we set the players locations. signs and moves
// All the data on the players should be on this member.
//
// Author: Roi Fogler && Motty Katz 
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _PLAYER_H
#define _PLAYER_H

#include "Point.h"
#include "Shoot.h"
#include "Direction.h"
#include "io_utils.h"

using namespace std;

class Player
{
private:
	// private DM
	Point locationPoint;
	Direction::value direction;
	
	unsigned int errorCounter, shootCounter, winCounter;

	// Private Methods
	void calcTargetPoint(Point& targetPoint);
public:
	unsigned int winCounter2;
	static const int PLAYER_1_X_POSITION = 10;
	static const int PLAYER_1_Y_POSITION = 9;
	static const int PLAYER_2_X_POSITION = 70;
	static const int PLAYER_2_Y_POSITION = 9;
	static const char PLAYER_1_SIGN = '@';
	static const char PLAYER_2_SIGN = '#';

	// Which player is that
	enum numberOfPlayer
	{
		One = 1,
		Two
	};

	enum maxErr{
		MAX_ERROR_FOR_MATH_GAME = 3
	};

	enum PLAYER_KEYS
	{
		PLAYER_1_DOWN = 'x',
		PLAYER_1_LEFT = 'a',
		PLAYER_1_RIGHT = 'd',
		PLAYER_1_UP = 'w', 
		PLAYER_2_DOWN = 'm',
		PLAYER_2_LEFT = 'j',
		PLAYER_2_RIGHT = 'l',
		PLAYER_2_UP = 'i',
		PLAYER_1_SHOOT = 'z',
		PLAYER_2_SHOOT = 'n'
	};

	// Ctor
	Player(numberOfPlayer number, Direction::value d = Direction::STAY);

	//---------------------------------------------------------------------------------------
	// this method updates the win counter
	//--------------------------------------------------------------------------------------

	// Getter && Setter
	void setDirection(Direction::value d){ direction = d; }
	Direction::value getDirection(){ return direction; }

	void setLocationPoint(const Point&);
	void setLocationPoint(unsigned int x, unsigned int y);

	Point getLocationPoint(){ return locationPoint; }
	Point getNextLocation();

	void addToErrorCounter(){++errorCounter;} 
	unsigned int getErrorCounter() const { return errorCounter; }
	void initErrorCounter(){ errorCounter = 0; }

	void addToWinCounter(){ ++winCounter; } 
	unsigned int getWinCounter() const { return winCounter; }
	void initWinCounter(){ winCounter = 0; }
	
	// Methods
	void printSighn();

	void move(Direction::value direction);

	Shoot* Player::shoot();
private:
	numberOfPlayer playerNumber;

public:
	// Getter && Setter
	void SetPlayerNumber(numberOfPlayer playerNumber1) { playerNumber = playerNumber1; }
	numberOfPlayer getPlayerNumber() const{ return playerNumber; }
};

#endif