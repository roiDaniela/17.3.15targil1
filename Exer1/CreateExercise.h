//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// CreateExercise.h
// -----------
// This file declares a
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

using namespace std;

class CreateExercise
{
private:

	// Varibles
	unsigned int a, b, result;
	unsigned int screenNumber;
	unsigned int hiddenValue;
	string hiddenExercise;
	static const int START_RANDOM_NUMBER = 1;
	static const int RANDOMIZE_INITNAL_DIFF = 10;

	enum Sighn
	{
		MINUS,
		PLUS,
		MULTI,
		DIVIDE
	};

	enum LocationOfVar
	{
		First,
		Second
	};

	Sighn sighn;

	// Methods
	Sighn randomSighn(){ return Sighn(rand() % 4); }
	LocationOfVar randomLocationOfVar(){ return LocationOfVar(rand() % 2); }
	unsigned int randomVar(){ return ((rand() % (screenNumber + RANDOMIZE_INITNAL_DIFF)) + START_RANDOM_NUMBER); }

public:
	//Ctor
	CreateExercise(unsigned int);

	// Methods
	unsigned int getHiddenValue(){ return hiddenValue; }
	string getHiddenExercise(){ return hiddenExercise; }
};

#endif