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
#include "Shoot.h"
#include "NumEaters.h"
#include "ColFlyers.h"
#include "RowFlyers.h"
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
	static const int RANDOM_NUMBERS_DIFF = 10;
	static const int FIRST_SERIES_OF_LEVELS = 20;

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
	RowFlyers rowFlyer1;
	RowFlyers rowFlyer2;
	ColFlyers colFlyer1;
	ColFlyers colFlyer2;
	NumEaters numEater1;
	NumEaters numEater2;
	list<Creature*> listOfFlyers;
	CreateExercise excersisePlayer_1;
	CreateExercise excersisePlayer_2;
	ScreenData GameDB;
	ResultLevel resultOfCurrLevel;
	list<Shoot> listOfShoots;
	
	bool stamB; //
	// private Methods
	void cleanShootList();
	void cleanFlyersCreatureList();
	void setKeyValues(Player::PLAYER_KEYS curr_input, bool& isPlayer1ShootedThisIteration, bool& isPlayer2ShootedThisIteration);
	void addRandomNunberToScreen(unsigned int currentLevel);
	bool iterationCounterIsBiggerThanAlowd() const;
	void setLevelResult(ResultLevel result){ resultOfCurrLevel = result; }
	ResultLevel getLevelResult() const{ return resultOfCurrLevel; }
	void setGameWinner(Player& player);
	bool isPlayersCrash(Player& pl1, Player& pl2 );
	void handlePlayersCrash(Player& pl1, Player& pl2);
	void handleWrongCatch(Player& pl, CreateExercise::ExerciseErrMsg ErrMsg);
	bool isWrongCatch(Player& pl,  CreateExercise::ExerciseErrMsg ErrMsg);
	void handlePlayerUsedAllErr(Player& pl, int currentLevel);
	bool isPlayerUsedAllErr(const Player& pl);
	void initPlayerToFirstPosition(Player::numberOfPlayer numberOfPlayer);
	void handleCreatureCrashNumber(const Point& p);
	void handleCreatureCrashPlayer(Player::numberOfPlayer numberOfPlayer, int currentLevel);
	Direction::value getNonStayDirection(const Player& p) const;
	void setThePrevDirection(Player::PLAYER_KEYS curr_input);
	bool cleanTwoDigitsFromScreen(Point pt);
	void handleShootCrashFlyer(unsigned int currentLevel);

public:
	// Getter && Setter
	unsigned int getIterationCounter() const { return iterationCounter; }
	void updateIterationCounter(){ iterationCounter++; }
	void updateShootCounter();
	void initParams(int currentLevel);
	ScreenData& GetDB();
	CreateExercise::ExerciseErrMsg checkExerciseSolved(Player& player, int currentLevel);
	void addFlyer(Creature* c);
	void RemoveCreature(Creature* c);
	void addShoot(const Shoot& s);
	CreateExercise& getExcercise(Player::numberOfPlayer playerNumber){ return ((playerNumber == Player::One) ? excersisePlayer_1: excersisePlayer_2); }
	void setExercise(Player::numberOfPlayer playerNumber, unsigned int currentLevel);

	// Ctor
	TheMathGame();
	
	//dtor
	//TheMathGame::~TheMathGame();
	
	// Public Methods
	bool isLevelDone(/*unsigned int currentLevel*/)const{
		return (getLevelResult(/*currentLevel*/) != NO_BODY_WON || iterationCounterIsBiggerThanAlowd()); }
	bool hasNextLevel(unsigned int currentLevel)const;
	void startLevel(unsigned int currentLevel);
	void doIteration(const list<char>& keyHits, unsigned int currentLevel);
	void doSubIteration(unsigned int currentLevel);
	void prepareStatusSentenceOnScreen();
	void resumeGame(unsigned int currentLevel);
	void initPoints(){ player1.initWinCounter(); player2.initWinCounter(); }
};
#endif _THEMATHGAME_H_

// END of NEW CODE EX1