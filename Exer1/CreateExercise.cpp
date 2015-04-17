
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// CreateExercise.cpp
// -----------
// This file responsible on the type: "exercise". this type shuold carries the exercise and its solution:
// The exercise to show and the hidden value. it is specialy for the guide of this game
//
// Author: Motty Katz  && Roi Fogler
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#include "CreateExercise.h"

//---------------------------------------------------------------------------------------
// Ctor
//---------------------------------------------------------------------------------------
CreateExercise::CreateExercise(unsigned int screenNumber1):screenNumber(screenNumber1){
	hiddenExercise = "";
	
	// randomise sighn
	sign = RandomOutput::CreateRandomSign();//randomSighn();

	switch (sign)
	{
	case Sign::MINUS:
		{
			b = randomVar();
			result = randomVar();

			a = result + b;

			// randomise who to hide
			LocationOfVarInExercise lv = randomLocationOfVar();
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
	case Sign::PLUS:
		{
			a = randomVar();
			b = randomVar();

			result = a + b;

			// randomise who to hide
			LocationOfVarInExercise lv = randomLocationOfVar();
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
	case Sign::MULT:
		{
			a = randomVar();
			b = randomVar();

			result = a * b;

			// randomise who to hide
			LocationOfVarInExercise lv = randomLocationOfVar();
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
	case Sign::DIV:
		{
			b = randomVar();
			result = randomVar();

			a = result * b;

			// randomise who to hide
			LocationOfVarInExercise lv = randomLocationOfVar();
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

			break; // Not realy needed
		}
		default:{ // if u reached here - uston we have a problem
			break;
		}
	}
}