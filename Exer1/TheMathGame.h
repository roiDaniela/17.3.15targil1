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
		ERROR_TWO_PLAYERS,
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
	list<Shoot> listOfShoots;
	
	// private Methods
	void cleanShootList();
	void setKeyValues(Player::PLAYER_KEYS curr_input);
	void addRandomNunberToScreen(unsigned int currentLevel);
	bool iterationCounterIsBiggerThanAlowd() const;
	void setLevelResult(ResultLevel result, unsigned int currentLevel){ arrayOfWinsInLevel[currentLevel] = result; }
	ResultLevel getLevelResult(int currentLevel) const{ return arrayOfWinsInLevel[currentLevel]; }
	void setGameWinner(Player& player, unsigned int currentLevel);
	bool isPlayersCrash(Player& pl1, Player& pl2 );
	void handlePlayersCrash(Player& pl1, Player& pl2);
	void handleWrongCatch(Player& pl, CreateExercise::ExerciseErrMsg ErrMsg);
	bool isWrongCatch(Player& pl,  CreateExercise::ExerciseErrMsg ErrMsg);
	void handlePlayerUsedAllErr(Player& pl, int currentLevel);
	bool isPlayerUsedAllErr(const Player& pl);
	void initPlayerToFirstPosition(Player::numberOfPlayer numberOfPlayer);
	void handleShootCrashNumber(list<Shoot>::iterator it);
	void handleShootCrashPlayer(Player::numberOfPlayer numberOfPlayer, int currentLevel);
	bool notDupShootInIteration();

public:
	// Getter && Setter
	unsigned int getIterationCounter() const { return iterationCounter; }
	void UpdateIterationCounter(){ iterationCounter++; }
	void UpdateShootCounter();
	void initParams(int currentLevel);
	ScreenData& GetDB();
	CreateExercise::ExerciseErrMsg checkExerciseSolved(Player& player, int currentLevel);
	void addShoot(const Shoot& s);
	CreateExercise& getExcercise(Player::numberOfPlayer playerNumber){ return ((playerNumber == Player::One) ? excersisePlayer_1: excersisePlayer_2); }
	void setExercise(Player::numberOfPlayer playerNumber, unsigned int currentLevel);

	// Ctor
	TheMathGame();
	
	//dtor
	TheMathGame::~TheMathGame();
	
	// Public Methods
	bool isLevelDone(unsigned int currentLevel)const{
		return (getLevelResult(currentLevel) != NO_BODY_WON || iterationCounterIsBiggerThanAlowd()); }
	bool hasNextLevel(unsigned int currentLevel)const;
	void startLevel(unsigned int currentLevel);
	void doIteration(const list<char>& keyHits, unsigned int currentLevel);
	void doSubIteration(unsigned int currentLevel);
	void prepareStatusSentenceOnScreen();
	void resumeGame(unsigned int currentLevel);
};
#endif _THEMATHGAME_H_

// END of NEW CODE EX1