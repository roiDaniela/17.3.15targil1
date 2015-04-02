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
	Point locationPoint;
	Direction::value direction;
	unsigned int errorCounter;
	static int winCounter_1;
	static int winCounter_2;

	bool isWin_1, isWin_2;

	static const int PLAYER_1_X_POSITION = 10;
	static const int PLAYER_1_Y_POSITION = 9;
	static const int PLAYER_2_X_POSITION = 70;
	static const int PLAYER_2_Y_POSITION = 9;
	
	// This Ctor shoudn't be in use
	//Player::Player(){ }
	
public:
	static const char PLAYER_1_SIGN = '@';
	static const char PLAYER_2_SIGN = '#';

	// Which player is that
	static enum numberOfPlayer
	{
		One = 1,
		Two
	};

	static enum MOVE_KEYS_PLAYER
	{
		PLAYER_1_DOWN = 'x',
		PLAYER_1_LEFT = 'a',
		PLAYER_1_RIGHT = 'd',
		PLAYER_1_UP = 'w', 
		PLAYER_2_DOWN = 'm',
		PLAYER_2_LEFT = 'j',
		PLAYER_2_RIGHT = 'l',
		PLAYER_2_UP = 'i'
	};

	static enum Result_winner
	{
		PLAYER_1_WON = 1,
		PLAYER_2_WON,
		TIE
	};

	// Ctor
	Player(numberOfPlayer number, Direction::value d = Direction::STAY);

	// dtor
	//~Player(){ delete locationPoint; }

	void updateWinCounter(){
		if (getPlayerNumber() == numberOfPlayer::One){
			winCounter_1 = (winCounter_1 != NULL) ? winCounter_1 : 0;
			winCounter_1++;
		}
		else if (getPlayerNumber() == numberOfPlayer::Two){
			winCounter_2 = (winCounter_2 != NULL) ? winCounter_2 : 0;
			winCounter_2++;
		}
	}

	int getWinCounter() const{
		if (getPlayerNumber() == numberOfPlayer::One){
			return winCounter_1;
		}
		else if (getPlayerNumber() == numberOfPlayer::Two){
			return winCounter_2;
		}
	}

	// Getter && Setter
	void setDirection(Direction::value d){ direction = d; }
	Direction::value getDirection(){ return direction; }

	void setLocationPoint(const Point&);
	void setLocationPoint(unsigned int x, unsigned int y);
	Point getLocationPoint(){ return locationPoint; }
	Point getNextLocation(Direction::value d);
	void setErrorCounter(unsigned int errorCounter1){ errorCounter = errorCounter1; }
	unsigned int getErrorCounter(){ return errorCounter; }

	void setIsWin(bool isWin){ ((getPlayerNumber() == numberOfPlayer::One) ? isWin_1 : isWin_2) = isWin; }
	bool getIsWin() const { return ((getPlayerNumber() == numberOfPlayer::One) ? isWin_1 : isWin_2); }

	// Methods
	void printSighn(){
		gotoxy(getLocationPoint());
		(playerNumber == numberOfPlayer::One) ? cout << PLAYER_1_SIGN : cout << PLAYER_2_SIGN;
	}

	void Player::move(Direction::value direction);

private:
	numberOfPlayer playerNumber;
	static Result_winner winner;
public:
	// Getter && Setter
	void SetPlayerNumber(numberOfPlayer playerNumber1) { playerNumber = playerNumber1; }
	numberOfPlayer getPlayerNumber() const{ return playerNumber; }
	static Result_winner getWinner(){ return winner; }
	static void setWinner(Result_winner winner1){ winner = winner1; }
};

#endif