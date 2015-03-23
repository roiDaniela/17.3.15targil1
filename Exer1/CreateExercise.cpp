
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// CreateExercise.cpp
// -----------
// This file 
//
// Author: Motty Katz  && Roi Fogler
// First version: 2015-03-22
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

#include "CreateExercise.h"

CreateExercise::CreateExercise(unsigned int screenNumber1):screenNumber(screenNumber1){
	hiddenExercise = "";
	sighn = randomSighn();

	switch (sighn)
	{
		case MINUS:
		{
			b = randomVar();
			result = randomVar();

			a = result + b;

			LocationOfVar lv = randomLocationOfVar();
			if (lv == First){
				hiddenExercise = to_string(a) + string(" - ") + string("_") + string(" = ") + to_string(result);
				hiddenValue = b;
			}
			else if (lv == Second){
				hiddenExercise = to_string(a)+string(" - ") + to_string(b) + string(" = ") + string("_");
				hiddenValue = result;
			}
			else{
				// if u reached here u have a problem
			}

			break;
		}
		case PLUS:
		{
			a = randomVar();
			b = randomVar();

			result = a + b;
			LocationOfVar lv = randomLocationOfVar();
			if (lv == First){
				hiddenExercise = string("_") + string(" + ") + to_string(b) + string(" = ") + to_string(result);
				hiddenValue = a;
			}
			else if (lv == Second){
				hiddenExercise = to_string(a) + string(" + ") + string("_") + string(" = ") + to_string(result);
				hiddenValue = b;
			}
			else{
				// if u reached here u have a problem
			}

			break;
		}
		case MULTI:
		{
			a = randomVar();
			b = randomVar();

			result = a * b;
			LocationOfVar lv = randomLocationOfVar();
			if (lv == First){
				hiddenExercise = string("_") + string(" * ") + to_string(b) + string(" = ") + to_string(result);
				hiddenValue = a;
			}
			else if (lv == Second){
				hiddenExercise = to_string(a) + string(" * ") + string("_") + string(" = ") + to_string(result);
				hiddenValue = b;
			}
			else{
				// if u reached here u have a problem
			}

			break;
		}
		case DIVIDE:
		{
			b = randomVar();
			result = randomVar();

			a = result * b;

			LocationOfVar lv = randomLocationOfVar();
			if (lv == First){
				hiddenExercise = to_string(a) + string(" / ") + string("_") + string(" = ") + to_string(result);
				hiddenValue = b;
			}
			else if (lv == Second){
				hiddenExercise = to_string(a) + string(" / ") + to_string(b) + string(" = ") + string("_");
				hiddenValue = result;
			}
			else{
				// if u reached here u have a problem
			}

			break;
		}
		default:{
			break;
		}
	}
}