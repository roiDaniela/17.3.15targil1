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
#include <math.h>

using namespace std;

class TheMathGame : public ISpecificGame
{
private:
	static const int TOTAL_NUMBER_OF_LEVELS = 20 /*3*/;
	static const int TOTAL_NUMBER_OF_CLOCK_TURNS = 1500 /*10*/;
	static const int TOTAL_NUMBER_OF_ERRORS = 3;
	unsigned int correctNumber_1, correctNumber_2; //
	unsigned int iterationCounter;
	Player player1; //
	Player player2; //
	ScreenData GameDB;

	// Methods
	void TheMathGame::setPlayerDirectionByKeyValue(Player::MOVE_KEYS_PLAYER curr_input);
	bool iterationCounterIsBiggerThanAlowd() const{
		if (getIterationCounter() > TOTAL_NUMBER_OF_CLOCK_TURNS){
			CleanTopOfScreen();
			writeOnScreenLocation(Lines::LINE_ONE_MIDDLE, "Its over than 1500 turns clock!!!!!");
			writeOnScreenLocation(Lines::LINE_THREE_RIGHT, "Points Player 1: " + to_string(player1.getWinCounter()));
			writeOnScreenLocation(Lines::LINE_THREE_LEFT, "Points Player 2: " + to_string(player2.getWinCounter()));
			Sleep(1500);
			return true;
		}

		return false;
	}

	void setGameWinner(){
		if (player1.getWinCounter() > player2.getWinCounter()){
			Player::setWinner(Player::Result_winner::PLAYER_1_WON);
		}
		else if (player1.getWinCounter() > player2.getWinCounter()){
			Player::setWinner(Player::Result_winner::PLAYER_2_WON);
		}
		else{
			Player::setWinner(Player::Result_winner::TIE);
		}
	}
public:
	// Getter && Setter
	unsigned int getIterationCounter() const { return iterationCounter; }
	void UpdateIterationCounter(){ iterationCounter++; }
	void initIterationCounter(){ iterationCounter = 0; }
	ScreenData& GetDB();
	
	// Ctor
	TheMathGame() : correctNumber_1(NULL), correctNumber_2(NULL), player1(Player::numberOfPlayer::One), player2(Player::numberOfPlayer::Two), iterationCounter(0){} ///*CurrentLevel(NULL),*/

	// Methods
	bool isLevelDone()const{ return (player1.getIsWin() || player2.getIsWin() || iterationCounterIsBiggerThanAlowd()); }
	bool hasNextLevel(unsigned int currentLevel)const{ return (currentLevel<=TOTAL_NUMBER_OF_LEVELS); }
	void startLevel( unsigned int currentLevel );
	void doIteration(const list<char>& keyHits, unsigned int currentLevel);
	void doSubIteration(unsigned int currentLevel);
	void prepareStatusSentenceOnScreen();
	void resumeGame();
};
#endif _THEMATHGAME_H_

// END of NEW CODE EX1