//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// CreateExercise.h
// -----------
// This file responsible on the type: "exercise". this type shuold carries the exercise and its solution:
// The exercise to show and the hidden value. it is specialy for the guide of this game
//
// Author: Roi Fogler && Motty Katz 
// First version: 2015-03-23
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

#ifndef _CREATE_EXERCISE_H
#define _CREATE_EXERCISE_H

#include <iostream>
#include <string>
#include "randomOutput.h"
#include <Windows.h>

using namespace std;

class CreateExercise
{
private:
	// private DM
	unsigned int a, b, result;
	unsigned int screenNumber;
	unsigned int hiddenValue;
	string hiddenExercise;
	static const int RANDOMIZE_INITNAL_DIFF = 10;

	enum LocationOfVarInExercise
	{
		First,
		Second
	};

	Sign::Operator sign;

	// Methods
	//---------------------------------------------------------------------------------------
	// random location of var specially fot the exercise
	//---------------------------------------------------------------------------------------
	LocationOfVarInExercise randomLocationOfVar(){ return LocationOfVarInExercise(RandomOutput::CreateRandomValue(2)); }

	//---------------------------------------------------------------------------------------
	// random var for the exercise
	//---------------------------------------------------------------------------------------
	unsigned int randomVar(){  return (RandomOutput::CreateRandomValue(screenNumber + RANDOMIZE_INITNAL_DIFF)); }

public:
	//Ctor
	CreateExercise(unsigned int);

	// Methods (Getters)
	unsigned int getHiddenValue(){ return hiddenValue; }
	string getHiddenExercise(){ return hiddenExercise; }
};

#endif