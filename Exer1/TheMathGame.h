//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Color.h
// ----------
// enum for colors.
//
// Author: Amir Kirsh
// First version: 2014-12-09
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

using namespace std;

class TheMathGame : public ISpecificGame
{
private:
	static const int TOTAL_NUMBER_OF_LEVELS = 20;
	static const int PLAYER_1_X_POSITION = 10;
	static const int PLAYER_1_Y_POSITION = 9;
	static const int PLAYER_2_X_POSITION = 70;
	static const int PLAYER_2_Y_POSITION = 9;
	static const char PLAYER_1_SIGN = '@';
	static const char PLAYER_2_SIGN = '#';
public:
	bool isLevelDone()const{return false;}
	bool hasNextLevel(unsigned int currentLevel)const{ return (currentLevel<=TOTAL_NUMBER_OF_LEVELS); }
	void startLevel( unsigned int currentLevel );
	void doIteration(const list<char>& keyHits);
	void doSubIteration();
};
#endif _THEMATHGAME_H_

// END of NEW CODE EX1