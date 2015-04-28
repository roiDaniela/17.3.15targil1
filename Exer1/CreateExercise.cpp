
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
		screenNumber -= 10;
		OpSign2 = RandomOutput::CreateRandomSign();
		CreateExercizeOfThreeVar(screenNumber, OpSign1, OpSign2);
		SetHiddenValues();
		SetExerciseToString();

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
	hiddenValue1 = HiddenValue;
	result = Result;
}


void CreateExercise::CreateExercizeOfThreeVar(unsigned int CurrentLevel, Sign::Operator OpSign1, Sign::Operator OpSign2){
	unsigned int a, b, c, res , Hidden1, Hidden2;
	switch (OpSign2)
	{
	case Sign::MINUS:
	{
		CreateExercizeOfTwoVar(CurrentLevel, OpSign1);
		a = num1;
		b = num2;
		c = RandomOutput::CreateRandomValue( 21 );
		if (OpSign1 == Sign::DIV)
			res = a / b - c;
		else if (OpSign1 == Sign::MULT)
			res = a * b - c;
		else if (OpSign1 == Sign::MINUS)
			res = a - b - c;
		else
			res = a + b - c;
		break;
	}
	case Sign::PLUS:
	{
		CreateExercizeOfTwoVar(CurrentLevel, OpSign1);
		a = num1;
		b = num2;
		c = RandomOutput::CreateRandomValue(21);
		if (OpSign1 == Sign::DIV)
			res = a / b + c;
		else if (OpSign1 == Sign::MULT)
			res = a * b + c;
		else if (OpSign1 == Sign::MINUS)
			res = a - b + c;
		else
			res = a + b + c;
		break;
	}
	case Sign::MULT:
	{
		if (OpSign1 != Sign::MULT && OpSign1 != Sign::DIV){
			if (OpSign1 == Sign::PLUS){
				a = RandomOutput::CreateRandomValue(21);
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
				res = RandomOutput::CreateRandomValue(b*c+22,b*c+1);
				a = res + (b * c);
			}
		}
		else{
			CreateExercizeOfTwoVar(CurrentLevel, OpSign1);
			a = num1;
			b = num2;
			c = RandomOutput::CreateRandomValue(21);
			res = (OpSign1 == Sign::DIV ? a / b * c : a * b * c);
		}
		break;
	}
	case Sign::DIV:
	{
		if (OpSign1 != Sign::MULT && OpSign1 != Sign::DIV){
			if (OpSign1 == Sign::PLUS){
				CreateExercizeOfTwoVar(CurrentLevel, OpSign2);
				b = num1;
				c = num2;
				a = RandomOutput::CreateRandomValue(21);
				res = a + b / c;
			}
			else
			{
				CreateExercizeOfTwoVar(CurrentLevel, OpSign2);
				b = num1;
				c = num2;
				res = RandomOutput::CreateRandomValue(20);
				a = res - (b / c);
			}
		}
		else{
			CreateExercizeOfTwoVar(CurrentLevel, OpSign1);
			a = num1;
			b = num2;
			c = RandomOutput::CreateRandomValue(21);
			res = (OpSign1 == Sign::DIV ? a / b / c : a * b / c);
		}
		break;
	}
	default:
		break;
	}

	num1 = a;
	num2 = b;
	num3 = c;
	result = res;
}

void CreateExercise::SetHiddenValues(){
	
	HiddenValuesLoc[0] = num1; HiddenValuesLoc[1] = num2; HiddenValuesLoc[2] = num3; HiddenValuesLoc[3] = result;
	if (((num1 < num2) && (num1 < num3)) || ((num1 < num2) && (num1 < result)) || ((num1 < num3) && (num1 < result)) ) {
		HiddenValuesLoc[0] = 0;
		hiddenValue1 = num1;
	}
	if (((num2 < num1) && (num2 < num3)) || ((num2 < num1) && (num2 < result)) || ((num2 < num3) && (num2 < result))){
		HiddenValuesLoc[1] = 0;
		if (hiddenValue1 == num1)
			hiddenValue2 = num2;
		else
			hiddenValue1 = num2;
	}
	if (((num3 < num2) && (num3 < num1)) || ((num3 < num1) && (num3 < result)) || ((num3 < num1) && (num3 < result))){
		HiddenValuesLoc[2] = 0;

		if (hiddenValue1 == num1 || hiddenValue1 == num2)
			hiddenValue2 = num3;
		else
			hiddenValue1 = num3;

	}
	if (((result < num2) && (result < num3)) || ((result < num2) && (result < num1)) || ((result < num3) && ( result < num1 ))){
		HiddenValuesLoc[3] = 0;
		hiddenValue2 = result;
	}
}

void CreateExercise::SetExerciseToString(){
	
	
	hiddenExercise = " " + to_string(HiddenValuesLoc[0]) + " " + ConvertSignToString(OpSign1)  +" " + to_string(HiddenValuesLoc[1]) +
		+" " + ConvertSignToString(OpSign2) + " " + to_string(HiddenValuesLoc[2]) + " = " + to_string(HiddenValuesLoc[3]) + " " ;

	hiddenExercise.replace(hiddenExercise.find(" 0 "), 3 ," _ "); 
	hiddenExercise.replace(hiddenExercise.find(" 0 "), 3 , " _ ");
}

string CreateExercise::ConvertSignToString(Sign::Operator OpSign){
	if (OpSign == Sign::DIV)
		return " / ";
	if (OpSign == Sign::MULT)
		return " * ";

	if (OpSign == Sign::PLUS)
		return " + ";
	if (OpSign == Sign::MINUS)
		return " - ";
}

bool CreateExercise::IsProblemSolved( unsigned int num ){
	bool is_solved = false;
	if (hiddenValue1 == num)
		return true;
	unsigned int tmp[4];
	memcpy( tmp, HiddenValuesLoc, 4 * sizeof( unsigned int ) );
	for (int i = 0; i < 4; i++){
		if (HiddenValuesLoc[i] == 0){
			tmp[i] = num;
			break;
		}
	}
	int res;
	if (tmp[3] == 0){
		switch (OpSign1)
		{
		case Sign::MINUS:{
			switch (OpSign2)
			{
			case Sign::MINUS:
				res = tmp[0] - tmp[1] - tmp[2];
				break;
			case Sign::PLUS:
				res = tmp[0] - tmp[1] + tmp[2];
				break;
			case Sign::MULT:
				res = tmp[0] - tmp[1] * tmp[2];
				break;
			case Sign::DIV:{
				res = tmp[0] - tmp[1] / tmp[2];
				if (tmp[1] % tmp[2] != 0) res = 22;
				break;
			}
			default:
				break;
			}
			break;
		}
		case Sign::PLUS:{
			switch (OpSign2)
			{
			case Sign::MINUS:
				res = tmp[0] + tmp[1] - tmp[2];
				break;
			case Sign::PLUS:
				res = tmp[0] + tmp[1] + tmp[2];
				break;
			case Sign::MULT:
				res = tmp[0] + tmp[1] * tmp[2];
				break;
			case Sign::DIV:{
				res = tmp[0] + tmp[1] / tmp[2];
				if (tmp[1] % tmp[2] != 0) res = 22;
				break;
			}
			default:
				break;
			}
			break;
		}
			break;
		case Sign::MULT:{
			switch (OpSign2)
			{
			case Sign::MINUS:
				res = tmp[0] * tmp[1] - tmp[2];
				break;
			case Sign::PLUS:
				res = tmp[0] * tmp[1] + tmp[2];
				break;
			case Sign::MULT:
				res = tmp[0] * tmp[1] * tmp[2];
				break;
			case Sign::DIV:{
				res = tmp[0] * tmp[1] / tmp[2];
				if (tmp[1] % tmp[2] != 0) res = 22;
				break;
			}
			default:
				break;
			}
			break;
		}
		case Sign::DIV:{
			if (tmp[0] % tmp[1] != 0) res = 22;
			else{

				switch (OpSign2)
				{
				case Sign::MINUS:
					res = tmp[0] / tmp[1] - tmp[2];
					break;
				case Sign::PLUS:
					res = tmp[0] / tmp[1] + tmp[2];
					break;
				case Sign::MULT:
					res = tmp[0] / tmp[1] * tmp[2];
					break;
				case Sign::DIV:{
					if (tmp[1] % tmp[2] != 0) res = 22;
					res = tmp[0] / tmp[1] / tmp[2];
					break;
				}
				default:
					break;
				}
			}
			break;
		}
			
		default:
			break;
		}
		is_solved = (res < 10000 && res > -10000);
		if (is_solved) hiddenValue1 = res;
		return is_solved;
	}
	else if (tmp[2] == 0){
		switch (OpSign1)
		{
		case Sign::MINUS:{
			switch (OpSign2)
			{
			case Sign::MINUS:
				res = result - tmp[0] + tmp[1];
				break;
			case Sign::PLUS:
				res = result - tmp[0] - tmp[1];
				break;
			case Sign::MULT:{
				if ((result - tmp[0]) % tmp[1] != 0) res = 22;
				else res = (result - tmp[0]) / -int(tmp[1]);
				break;
			}
			case Sign::DIV:
				if (tmp[1] % (result - tmp[0]) != 0) res = 22;
				else res = -int(tmp[1]) / (result - tmp[0]);
				break;
			default:
				break;
			}
			break;
		}
		case Sign::PLUS:{
			switch (OpSign2)
			{
			case Sign::MINUS:
				res = result - tmp[0] + tmp[1];
				break;
			case Sign::PLUS:
				res = result - tmp[0] - tmp[1];
				break;
			case Sign::MULT:
				if ((result - tmp[0]) % tmp[1] != 0) res = 22;
				else res = (result - tmp[0]) / int(tmp[1]);
				break;
			case Sign::DIV:
				if (tmp[1] % (result - tmp[0]) != 0) res = 22;
				else res = -int(tmp[1]) / (result - tmp[0]);
				break;
			default:
				break;
			}
			break;
		}
		case Sign::MULT:{
			switch (OpSign2)
			{
			case Sign::MINUS:
				res = result - tmp[0] * tmp[1];
				break;
			case Sign::PLUS:
				res = result - tmp[0] * tmp[1];
				break;
			case Sign::MULT:
				if (result % (tmp[0] * tmp[1]) == 0) res = 22;
				else res = result / (tmp[0] * tmp[1]);
				break;
			case Sign::DIV:
				if ((tmp[0] * tmp[1]) % result == 0) res = 22;
				else res = (tmp[0] * tmp[1]) / result;
				break;
			default:
				break;
			}
			break;
		}
		case Sign::DIV:{
			switch (OpSign2)
			{
			case Sign::MINUS:
				if (tmp[0] % tmp[1] != 0) res = 22;
				else res = result - tmp[0] / tmp[1];
				break;
			case Sign::PLUS:
				if (tmp[0] % tmp[1] != 0) res = 22;
				else res = result - tmp[0] / tmp[1];
				break;
			case Sign::MULT:
				if (tmp[0] % tmp[1] != 0) res = 22;
				else res = result / (tmp[0] / tmp[1]);
				break;
			case Sign::DIV:
				if (tmp[0] % tmp[1] != 0) res = 22;
				else res = (tmp[0] / tmp[1]) / result;
				break;
			default:
				break;
			}
			break;
		}
		default:
			break;
		}

		is_solved = (res < 22 && res > 0) || (res > -22 && res < 0);
		if (is_solved) hiddenValue1 = res;
		return is_solved;
	}
	else if (tmp[1] == 0){
		switch (OpSign1)
		{
		case Sign::MINUS:{
			switch (OpSign2)
			{
			case Sign::MINUS:
				res = result - tmp[0] + tmp[2];
				break;
			case Sign::PLUS:
				res = result - tmp[0] - tmp[2];
				break;
			case Sign::MULT:{
				if ((result - tmp[0]) % tmp[2] != 0) res = 22;
				else res = (result - tmp[0]) / int(tmp[2]);
				break;
			}
			case Sign::DIV:
				res = (result - tmp[0])*tmp[2];
				break;
			default:
				break;
			}
			break;
		}
		case Sign::PLUS:{
			switch (OpSign2)
			{
			case Sign::MINUS:
				res = result - tmp[0] + tmp[2];
				break;
			case Sign::PLUS:
				res = result - tmp[0] - tmp[2];
				break;
			case Sign::MULT:
				if ((result - tmp[0]) % tmp[2] != 0) res = 22;
				else res = (result - tmp[0]) / tmp[2];
				break;
			case Sign::DIV:
				res = (result - tmp[0]) * tmp[2];
				break;
			default:
				break;
			}
			break;
		}
		case Sign::MULT:{
			switch (OpSign2)
			{
			case Sign::MINUS:
				if ((result + tmp[2]) % tmp[0] != 0) res = 22;
				else res = (result + tmp[2]) / tmp[0];
				break;
			case Sign::PLUS:
				if ((result - tmp[2]) % tmp[0] != 0) res = 22;
				else res = (result - tmp[2]) / tmp[0];
				break;
			case Sign::MULT:
				if (result % tmp[2] !=0  || result % tmp[0] != 0) res = 22;
				else res = result / tmp[0] / tmp[2];
				break;
			case Sign::DIV:
				if (result * tmp[2]  %  tmp[0] != 0) res = 22;
				else res = result * tmp[2] / tmp[0];
				break;
			default:
				break;
			}
			break;
		}
		case Sign::DIV:{
			switch (OpSign2)
			{
			case Sign::MINUS:
				if ((result + tmp[2]) % tmp[0] != 0) res = 22;
				else res = (result + tmp[2]) / tmp[0];
				break;
			case Sign::PLUS:
				if ((result - tmp[2]) % tmp[0] != 0) res = 22;
				else res = (result - tmp[2]) / tmp[0];				
				break;
			case Sign::MULT:
				if (tmp[0] % (result / tmp[2]) != 0) res = 22;
				else res = tmp[0] % (result / tmp[2]);
				break;
			case Sign::DIV:
				if (tmp[0] % (result / tmp[2]) != 0) res = 22;
				else res = (tmp[0] / result / tmp[2]);
				break;
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
		is_solved = (res < 22 && res > 0) || (res > -22 && res < 0);
		if (is_solved) hiddenValue1 = res;
		return is_solved;
	}
	/*if (HiddenValuesLoc[0] == 0){
		if (OpSign1 == Sign::PLUS || OpSign1 == Sign::MINUS) {
			if (HiddenValuesLoc[3] != 0)
				res = result - HiddenValuesLoc[3];
			if (HiddenValuesLoc[2] == 0){
				if (OpSign2 == Sign::DIV)
					if (OpSign1 == Sign::PLUS)
						res *= num3;
					else
						res *= -int(num3);
				else if (OpSign2 == Sign::MULT)
					if (OpSign1 == Sign::PLUS)
						res = res % num3 == 0 ? res /= num3 : 0 ;
					else
						res = res % num3 == 0 ?  res /= -int(num3) : 0;
			}
		}
	}
	*/
	return true;
}