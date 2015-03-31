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
	static const int TOTAL_NUMBER_OF_LEVELS = 3 /*20*/;
	static const int TOTAL_NUMBER_OF_CLOCK_TURNS = 10 /*1500*/;

	unsigned int correctNumber_1, correctNumber_2; //
	unsigned int iterationCounter;
	Player* player1; //
	Player* player2; //
	ScreenData GameDB;

	// Methods
	void TheMathGame::setPlayerDirectionByKeyValue(Player::MOVE_KEYS_PLAYER curr_input);
	bool iterationCounterIsBiggerThanAlowd() const{
		if (getIterationCounter() > TOTAL_NUMBER_OF_CLOCK_TURNS){
			writeOnTopOfScreen("Its over than 1500 turns clock!!!!");
			return true;
		}

		return false;
	}
public:
	// Getter && Setter
	unsigned int getIterationCounter() const { return iterationCounter; }
	void UpdateIterationCounter(){ iterationCounter++; }
	void initIterationCounter(){ iterationCounter = 0; }

	// Ctor
	TheMathGame() : correctNumber_1(NULL), correctNumber_2(NULL), player1(NULL), player2(NULL), iterationCounter(0){} ///*CurrentLevel(NULL),*/

	// Methods
	bool isLevelDone()const{ return (player1->getIsWin() || player2->getIsWin() || iterationCounterIsBiggerThanAlowd()); }
	bool hasNextLevel(unsigned int currentLevel)const{ return (currentLevel<=TOTAL_NUMBER_OF_LEVELS); }
	void startLevel( unsigned int currentLevel );
	void doIteration(const list<char>& keyHits, unsigned int currentLevel);
	void doSubIteration(unsigned int currentLevel);
};
#endif _THEMATHGAME_H_

// END of NEW CODE EX1