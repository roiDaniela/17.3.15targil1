
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
	// randomise sighn
	OpSign1 = RandomOutput::CreateRandomSign();//randomSighn();

	if (!screenNumber > 20){
		CreateExercizeOfTwoVar(screenNumber,OpSign1);
	}
	else{
		OpSign2 = RandomOutput::CreateRandomSign();
		CreateExercizeOfThreeVar(screenNumber, OpSign1, OpSign2);
	}
}

void CreateExercise::CreateExercizeOfTwoVar(unsigned int CurrentLevel, Sign::Operator OpSign){
	hiddenExercise = "";
	unsigned int a, b, Result, HiddenValue;
		switch (OpSign)
		{
		case Sign::MINUS:
		{
			b = randomVar();
			Result = randomVar();

			a = Result + b;

			// randomise who to hide
			LocationOfVarInExercise lv = randomLocationOfVar();
			if (lv == First){
				hiddenExercise = to_string(a) + string(" - ") + string("_") + string(" = ") + to_string(Result);
				HiddenValue = b;
			}
			else if (lv == Second){
				hiddenExercise = to_string(a) + string(" - ") + to_string(b) + string(" = ") + string("_");
				HiddenValue = Result;
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

			Result = a + b;

			// randomise who to hide
			LocationOfVarInExercise lv = randomLocationOfVar();
			if (lv == First){
				hiddenExercise = string("_") + string(" + ") + to_string(b) + string(" = ") + to_string(Result);
				HiddenValue = a;
			}
			else if (lv == Second){
				hiddenExercise = to_string(a) + string(" + ") + string("_") + string(" = ") + to_string(Result);
				HiddenValue = b;
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

			Result = a * b;

			// randomise who to hide
			LocationOfVarInExercise lv = randomLocationOfVar();
			if (lv == First){
				hiddenExercise = string("_") + string(" * ") + to_string(b) + string(" = ") + to_string(Result);
				HiddenValue = a;
			}
			else if (lv == Second){
				hiddenExercise = to_string(a) + string(" * ") + string("_") + string(" = ") + to_string(Result);
				HiddenValue = b;
			}
			else{
				// if u reached here u have a problem
			}

			break;
		}
		case Sign::DIV:
		{
			b = randomVar();
			Result = randomVar();

			a = Result * b;

			// randomise who to hide
			LocationOfVarInExercise lv = randomLocationOfVar();
			if (lv == First){
				hiddenExercise = to_string(a) + string(" / ") + string("_") + string(" = ") + to_string(Result);
				HiddenValue = b;
			}
			else if (lv == Second){
				hiddenExercise = to_string(a) + string(" / ") + to_string(b) + string(" = ") + string("_");
				HiddenValue = Result;
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
	
	num1 = a;
	num2 = b;
	result = Result;
}


void CreateExercise::CreateExercizeOfThreeVar(unsigned int CurrentLevel, Sign::Operator OpSign1, Sign::Operator OpSign2){
	unsigned int a, b, c, res , Hidden1, Hidden2;
	switch (OpSign2)
	{
	case Sign::MINUS:
	{
		break;
	}
	case Sign::PLUS:
	{
		CreateExercizeOfTwoVar( CurrentLevel, OpSign1 );
		a = num1;
		b = num2;
		c = RandomOutput::CreateRandomValue(20);
		//res = ?;
		break;
	}
	case Sign::MULT:
		if (OpSign1 != Sign::MULT && OpSign1 != Sign::DIV){
			if (OpSign1 == Sign::PLUS){
				a = RandomOutput::CreateRandomValue(20);
				CreateExercizeOfTwoVar(CurrentLevel, OpSign2);
				b = num1;
				c = num2;
				res = a + b * c;
			}
			else
			{
				CreateExercizeOfTwoVar(CurrentLevel, OpSign2);
				b = num1;
				c = num2;
				res = RandomOutput::CreateRandomValue(20);
				a = res - (b + c);
			}
		}
		else{
			CreateExercizeOfTwoVar(CurrentLevel, OpSign1);
			a = num1;
			b = num2;
			c = RandomOutput::CreateRandomValue(21);

		}
		break;
	case Sign::DIV:
		break;
	default:
		break;
	}
}