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

using namespace std;

class CreateExercise
{
private:
	// private DM
	int num1, num2, num3,result;
	unsigned int screenNumber;
	unsigned int hiddenValue1, hiddenValue2;
	string hiddenExercise;
	static const int RANDOMIZE_INITNAL_DIFF = 10;

	enum LocationOfVarInExercise
	{
		First,
		Second
	};

	Sign::Operator OpSign1, OpSign2;

	// Methods
	//---------------------------------------------------------------------------------------
	// random location of var specially fot the exercise
	//---------------------------------------------------------------------------------------
	LocationOfVarInExercise randomLocationOfVar(){ return LocationOfVarInExercise(RandomOutput::CreateRandomValue(2)); }
	void CreateExercizeOfTwoVar(unsigned int CurrentLevel, Sign::Operator OpSign );
	void CreateExercizeOfThreeVar(unsigned int CurrentLevel, Sign::Operator OpSign1, Sign::Operator OpSign2);
	void SetHiddenValues();
	void SetExerciseToString();
	
	string ConvertSignToString(Sign::Operator OpSign);
	
	//---------------------------------------------------------------------------------------
	// random var for the exercise
	//---------------------------------------------------------------------------------------
	unsigned int randomVar(){  return (RandomOutput::CreateRandomValue(screenNumber + RANDOMIZE_INITNAL_DIFF)); }

public:
	//Ctor
	CreateExercise(unsigned int);

	enum ExerciseErrMsg{ SOLVED = 5000, WAIT_FOR_SECOND_PARAM, WRONG_VALUE, PLAYER_ONE_VALUE_INSERTED = 35, 
						 PLAYER_TWO_VALUE_INSERTED = 64, INITIATING_VALUE_FROM_21TH_LEVEL = 10,
						 THREE_VARIABLES_EXERCISE_STARTING_LEVEL = 21};
	// Methods (Getters)
	unsigned int getHiddenValue1(){ return hiddenValue1; }
	unsigned int getHiddenValue2(){ return hiddenValue2; }
	string getHiddenExercise(){ return hiddenExercise; }
	ExerciseErrMsg IsProblemSolved(unsigned int num);
	
};

#endif