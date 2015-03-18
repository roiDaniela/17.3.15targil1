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

public:
	bool isLevelDone()const{return false;}
	bool hasNextLevel()const{return true;}
	void startLevel(){}
	void doIteration(const list<char>& keyHits){}
	void doSubIteration(){}
};
#endif _THEMATHGAME_H_

// END of NEW CODE EX1