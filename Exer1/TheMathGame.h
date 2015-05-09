//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// TheMathGame.h
// ----------
// This file responsible for the logical part of the game. its realizes the exercise and moves the players.
// The 2 major methods are: startLevel, doIteration. we added other helper methods to realize the logic.
//
// Author: Roi Fogler & Motty katz
// First version: 2015-03-18
// 
// This code is part of a solution for "the math game" excercise 1 in C++ course, Semester A 2015
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


// NEW CODE EX1, author=<Motty Katz && Roi Fogler>, date=<2015-03-18>

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
	// Consts
	static const int TOTAL_NUMBER_OF_LEVELS = 40;
	static const int TOTAL_NUMBER_OF_CLOCK_TURNS = 1500;
	static const int TOTAL_NUMBER_OF_ERRORS = 3;
	static const int SHOOT_PER_ITERATION = 200;

	enum ResultLevel
	{
		PLAYER_ONE_WON = 1,
		PLAYER_TWO_WON,
		TIE,
		NO_BODY_WON
	};

	// private DM
	unsigned int iterationCounter;
	Player player1;
	Player player2;
	CreateExercise excersisePlayer_1;
	CreateExercise excersisePlayer_2;
	ScreenData GameDB;
	ResultLevel arrayOfWinsInLevel[1 + TOTAL_NUMBER_OF_LEVELS];
	list<Shoot*> listOfShoots;
	
	// praivte Methods
	void cleanShootList();
	void setKeyValues(Player::PLAYER_KEYS curr_input);
	void addRandomNunberToScreen(unsigned int currentLevel);
	bool iterationCounterIsBiggerThanAlowd() const;
	void setLevelResult(ResultLevel result, unsigned int currentLevel){ arrayOfWinsInLevel[currentLevel] = result; }
	void setGameWinner(Player& player, unsigned int currentLevel);

public:
	// Getter && Setter
	unsigned int getIterationCounter() const { return iterationCounter; }
	void UpdateIterationCounter(){ iterationCounter++; }
	void UpdateShootCounter();
	void initParams(int currentLevel);
	ScreenData& GetDB();
	void addShoot(Shoot* s);

	//---------------------------------------------------------------------------------------
	// this function gets the player and returns its exercise as the new type: exercise
	//---------------------------------------------------------------------------------------
	CreateExercise& getExcercise(Player::numberOfPlayer playerNumber){ return ((playerNumber == Player::One) ? excersisePlayer_1: excersisePlayer_2); }
	
	//---------------------------------------------------------------------------------------
	// this function gets the player and curr level and sets the exercise
	//---------------------------------------------------------------------------------------
	void setExercise(Player::numberOfPlayer playerNumber, unsigned int currentLevel){
		if (playerNumber == Player::One){
			excersisePlayer_1 = CreateExercise(currentLevel);
		}
		else{
			excersisePlayer_2 = CreateExercise(currentLevel);
		}
	}

	//---------------------------------------------------------------------------------------
	// Ctor
	//---------------------------------------------------------------------------------------
	TheMathGame();
	
	TheMathGame::~TheMathGame();
	// Public Methods
	//---------------------------------------------------------------------------------------
	// this functuin checks if the level finished
	//---------------------------------------------------------------------------------------
	bool isLevelDone(unsigned int currentLevel)const{
		return (arrayOfWinsInLevel[currentLevel] != NO_BODY_WON || iterationCounterIsBiggerThanAlowd()); }
	
	//---------------------------------------------------------------------------------------
	// this function checks if there is another level, otherwise game ended and 
	// prints the winner
	//---------------------------------------------------------------------------------------
	bool hasNextLevel(unsigned int currentLevel)const {
		bool result = (currentLevel < TOTAL_NUMBER_OF_LEVELS);
		
		// Check if game finished so print the winner
		string sentence = "";

		if (!result){
			CleanTopOfScreen();
			
			if (player1.getWinCounter() > player2.getWinCounter()){
				sentence = "PLAYER 1 WON !!";
			}
			else if (player1.getWinCounter() < player2.getWinCounter()){
				sentence = "PLAYER 2 WON !!";
			}
			// tie
			else{
				sentence = "IT WAS TIE";
			}

			writeOnScreenLocation(Lines::LINE_ONE_MIDDLE, sentence);
		}

		return result;
	}
	void startLevel(unsigned int currentLevel);
	void doIteration(const list<char>& keyHits, unsigned int currentLevel);
	void doSubIteration(unsigned int currentLevel);
	void prepareStatusSentenceOnScreen();
	void resumeGame(unsigned int currentLevel);
};
#endif _THEMATHGAME_H_

// END of NEW CODE EX1