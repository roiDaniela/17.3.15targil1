//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// TheMathGame.h
// ----------
//
// Author: Roi Fogler & Motty katz
// First version: 2015-03-18
// 
// This code is part of a solution for "the space ships game" excercise 1 in C++ course, Semester A 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// In the file itself, add above each change/addition a remark saying: "NEW CODE EX2, author=<name>, date=<YYYY-MM-DD>"
// and close it at the end with a remark saying "END of NEW CODE EX2" 
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// NEW CODE EX1, author=<Motty>, date=<2015-03-18>

#ifndef _THEMATHGAME_H_
#define _THEMATHGAME_H_

#include <iostream>
#include "GameManager.h"
#include "io_utils.h"
#include "Player.h"

using namespace std;

class TheMathGame : public ISpecificGame
{
private:
	static const int TOTAL_NUMBER_OF_LEVELS = 20;
	
	Player* player1; //
	Player* player2; //
	unsigned int correctNumber; //
	unsigned int CurrentLevel;
	ScreenData GameDB;

	// Methods
	void TheMathGame::setPlayerDirectionByKeyValue(Player::MOVE_KEYS_PLAYER curr_input);
public:
	TheMathGame() :correctNumber(NULL), player1(NULL), player2(NULL){} //
	bool isLevelDone()const{return false;}
	bool hasNextLevel(unsigned int currentLevel)const{ return (currentLevel<=TOTAL_NUMBER_OF_LEVELS); }
	void startLevel( unsigned int currentLevel );
	void doIteration(const list<char>& keyHits);
	void doSubIteration();
};
#endif _THEMATHGAME_H_

// END of NEW CODE EX1