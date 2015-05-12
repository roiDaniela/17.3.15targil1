
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

	if (screenNumber < THREE_VARIABLES_EXERCISE_STARTING_LEVEL ){
		CreateExercizeOfTwoVar(screenNumber,OpSign1);
	}
	else{
		//screenNumber -= 10;
		
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

			break;
		}
		case Sign::PLUS:
		{
			a = randomVar();
			b = randomVar();

			Result = a + b;

			break;
		}
		case Sign::MULT:
		{
			a = randomVar();
			b = randomVar();

			Result = a * b;

			break;
		}
		case Sign::DIV:
		{
			b = randomVar();
			Result = randomVar();

			a = Result * b;

			break; // Not realy needed
		}
		default:{ // if u reached here - uston we have a problem
			break;
		}
		}
	
	num1 = a;
	num2 = b;
	result = Result;

	SetHiddenValues();
	SetExerciseToString();
}


void CreateExercise::CreateExercizeOfThreeVar(unsigned int CurrentLevel, Sign::Operator OpSign1, Sign::Operator OpSign2){
	unsigned int a, b, c, res,copyCurrLevl = screenNumber ;
	screenNumber = INITIATING_VALUE_FROM_21TH_LEVEL;
	switch (OpSign2)
	{
	case Sign::MINUS:
	{
		CreateExercizeOfTwoVar(CurrentLevel, OpSign1);
		a = num1;
		b = num2;
		while (result <= 3){
			CreateExercizeOfTwoVar(CurrentLevel, OpSign1);
			a = num1;
			b = num2;
		}

		if (OpSign1 == Sign::DIV){
			c = RandomOutput::CreateRandomValue(a / b - 1);
			res = a / b - c;
			
		}
		else if (OpSign1 == Sign::MULT){
			c = RandomOutput::CreateRandomValue(a * b - 1);
			res = a * b - c;
		}
		else if (OpSign1 == Sign::MINUS){
			c = RandomOutput::CreateRandomValue(a - b - 1);
			res = a - b - c;
		}
		else{
			c = RandomOutput::CreateRandomValue(a + b - 1);
			res = a + b - c;
		}
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

	screenNumber = copyCurrLevl;
	SetHiddenValues();
	SetExerciseToString();
}


void CreateExercise::SetHiddenValues(){
	unsigned int TmpCpy[4] = { num1, num2, num3, result };
	hiddenValue1 = hiddenValue2 = 0;

	// Check what level we are in order to decide the algorithm
	if (screenNumber < THREE_VARIABLES_EXERCISE_STARTING_LEVEL){
		LocationOfVarInExercise lv = randomLocationOfVar();
		if (OpSign1 == Sign::PLUS || OpSign1 == Sign::MULT)
			hiddenValue1 = (lv == First) ? num1 : num2;
		else
			hiddenValue1 = (lv == First) ? num2 : result;
	}
	else {
		
		// Take the 2 minimal values can be also equal
		if (((num1 <= num2) && (num1 <= num3)) || ((num1 <= num2) && (num1 <= result)) || ((num1 <= num3) && (num1 <= result))) {
			// Set as an hidden value and set the tmpcopy to 0 as it should be
			hiddenValue1 = num1;
			TmpCpy[0] = 0;
		}
		if (((num2 <= num1) && (num2 <= num3)) || ((num2 <= num1) && (num2 <= result)) || ((num2 <= num3) && (num2 <= result))){
			// Check first that hidden value 1 is not initiated allready
			// Set as an hidden value and set the tmpcopy to 0 as it should be
			if (hiddenValue1 == num1)
				hiddenValue2 = num2;
			else
				hiddenValue1 = num2;

			TmpCpy[1] = 0;
		}
		// Check first that hidden value 1 or hidden value 2 is not initiated allready
		// Set as an hidden value and set the tmpcopy to 0 as it should be
		if (((num3 <= num2) && (num3 <= num1)) || ((num3 <= num1) && (num3 <= result)) || ((num3 <= result) && (num3 <= num2))){
			if (hiddenValue1 == 0 || hiddenValue2 == 0){
				if (hiddenValue1 == 0)
					hiddenValue1 = num3;
				else if (hiddenValue2 == 0)
					hiddenValue2 = num3;
				TmpCpy[2] = 0;
			}
		}
		// Check first that hidden value 2 is not initiated allready
		// Set as an hidden value and set the tmpcopy to 0 as it should be
		// Set result to 0, not needed for further calculations
		if (((result <= num2) && (result <= num3)) || ((result <= num2) && (result <= num1)) || ((result <= num3) && (result <= num1))){
			if (hiddenValue2 == 0){
				hiddenValue2 = result;
				result = 0;
			}
		}

		// Set the number back with 0 in the hidden values
		num1 = TmpCpy[0]; num2 = TmpCpy[1]; num3 = TmpCpy[2];
	}
}


void CreateExercise::SetExerciseToString(){
	// Check what level we are in order to decide the algorithm
	if (screenNumber < THREE_VARIABLES_EXERCISE_STARTING_LEVEL){
		hiddenExercise = " " + to_string( num1 ) + " " + ConvertSignToString(OpSign1) + " " + to_string( num2 ) + string("  =  ") + to_string(result) + " ";
		
		// Repalce the 0 value with _
		hiddenExercise.replace(hiddenExercise.find(" " + to_string(hiddenValue1) + " " ), to_string(hiddenValue1).length()+1, "_");
	}
	else{
		
		hiddenExercise = " " + to_string(num1) + " " + ConvertSignToString(OpSign1) + " " + to_string(num2) +
						 " " + ConvertSignToString(OpSign2) + " " + to_string(num3) + "  =  " + to_string(result) + " ";
		
		// Repalce the 0 value with _
		string::size_type t = hiddenExercise.find(" 0 ");
		hiddenExercise.replace(t, 3, "_");
		t = hiddenExercise.find(" 0 ");
		hiddenExercise.replace(t, 3, "_");
	}
}

string CreateExercise::ConvertSignToString(Sign::Operator OpSign){
	if (OpSign == Sign::DIV)
		return " / ";
	if (OpSign == Sign::MULT)
		return " * ";
	if (OpSign == Sign::PLUS)
		return " + ";
	
	return " - ";
}


CreateExercise::ExerciseErrMsg CreateExercise::IsProblemSolved(unsigned int num){
	ExerciseErrMsg is_solved = WRONG_VALUE;
	const int MAX_RESULT = screenNumber + RANDOMIZE_INITNAL_DIFF;

		// Case eaten one of the following, value not found is in case empty 
		if (num == ScreenData::VALUE_NOT_FOUND || num == PLAYER_ONE_VALUE_INSERTED || num == PLAYER_TWO_VALUE_INSERTED)
			return is_solved;

	// Case it's true it means that or the problem 
	// solved or the system waiting for second param
	// in that case hidden value 2 will not be 0
	if (hiddenValue1 == num){
		hiddenValue1 = hiddenValue2;
		hiddenValue2 = 0;
		if (hiddenValue1 == 0)
			return (SOLVED);
		return WAIT_FOR_SECOND_PARAM;
	}
	else{
		if (hiddenValue2 == 0)
			return WRONG_VALUE;
	}

	// copy new numbers with 0 in the variable spot and set the value inserted by the user
	int tmp[4] = { num1, num2, num3, result };
	for (int i = 0; i < 4; i++)
		if (tmp[i] == 0){
			tmp[i] = num;
			break;
		}


	// In general I solved it like one variable equation, 
	// moved the variable aside and calculated it's value
	// needed to follow the basic arithmatic rules 


	// Go over the cases possible if the variable is in result
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
				if (tmp[1] % tmp[2] != 0) res = MAX_RESULT;
				res = tmp[0] - tmp[1] / tmp[2];
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
				if (tmp[1] % tmp[2] != 0) res = MAX_RESULT;
				else res = tmp[0] + tmp[1] / tmp[2];

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
				if (tmp[1] % tmp[2] != 0) res = MAX_RESULT;
				else res = tmp[0] * tmp[1] / tmp[2];
				break;
			}
			default:
				break;
			}
			break;
		}
		case Sign::DIV:{
			if (tmp[0] % tmp[1] != 0) res = MAX_RESULT;
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
					if (tmp[1] % tmp[2] != 0) res = MAX_RESULT;
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

	}

	// Go over the cases possible if the variable is in num3
	else if (tmp[2] == 0){
		switch (OpSign1)
		{
		case Sign::MINUS:{
			switch (OpSign2)
			{
			case Sign::MINUS:{
				res = tmp[0] - tmp[1] - result;
				if (tmp[0] - tmp[1] - res != result) res = MAX_RESULT;
				break;
			}
			case Sign::PLUS:
				res = result - tmp[0] + tmp[1];
				break;
			case Sign::MULT:{
				if (abs(int(result - tmp[0])) % tmp[1] != 0) res = MAX_RESULT;
				else res = abs(int(result - tmp[0])) / int(tmp[1]);
				break;
			}
			case Sign::DIV:
				if (tmp[1] % (result - tmp[0]) != 0) res = MAX_RESULT;
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
				res = tmp[0] + tmp[1] - tmp[3];
				break;
			case Sign::PLUS:
				res = result - tmp[0] - tmp[1];
				break;
			case Sign::MULT:
				if ((result - tmp[0]) % tmp[1] != 0) res = MAX_RESULT;
				else res = (result - tmp[0]) / int(tmp[1]);
				break;
			case Sign::DIV:
				if (tmp[1] % (result - tmp[0]) != 0) res = MAX_RESULT;
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
				if (result % (tmp[0] * tmp[1]) != 0) res = MAX_RESULT;
				else res = result / (tmp[0] * tmp[1]);
				break;
			case Sign::DIV:
				if ((tmp[0] * tmp[1]) % result != 0) res = MAX_RESULT;
				else res = (tmp[0] * tmp[1]) / result;
				break;
			default:
				break;
			}
			break;
		}
		case Sign::DIV:{
			if (tmp[0] % tmp[1] != 0)
				res = MAX_RESULT;
			else{
				switch (OpSign2)
				{
				case Sign::MINUS:
					res = result - tmp[0] / tmp[1];
					break;
				case Sign::PLUS:
					res = result - tmp[0] / tmp[1];
					break;
				case Sign::MULT:
					res = result / (tmp[0] / tmp[1]);
					break;
				case Sign::DIV:
					res = (tmp[0] / tmp[1]) / result;
					break;
				default:
					break;
				}
			}
			break;
		}
		default:
			break;
		}

	}
	// Go over the cases possible if the variable is in num2
	// Needed to make sure there is no fractions or division by 0
	// In case that happends res will be set so it will return "wrong answer"
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
				if ((result - tmp[0]) % tmp[2] != 0) res = MAX_RESULT;
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
				if ((result - tmp[0]) % tmp[2] != 0) res = MAX_RESULT;
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
						// Needed to make sure there is no fractions or division by 0
						// In case that happends res will be set so it will return "wrong answer"
		case Sign::MULT:{
			switch (OpSign2)
			{
			case Sign::MINUS:
				if ((result + tmp[2]) % tmp[0] != 0) res = MAX_RESULT;
				else res = (result + tmp[2]) / tmp[0];
				break;
			case Sign::PLUS:
				if ((result - tmp[2]) % tmp[0] != 0) res = MAX_RESULT;
				else res = (result - tmp[2]) / tmp[0];
				break;
			case Sign::MULT:
				if (result % tmp[2] != 0 || result % tmp[0] != 0) res = MAX_RESULT;
				else res = result / tmp[0] / tmp[2];
				break;
			case Sign::DIV:
				if (result * tmp[2] % tmp[0] != 0) res = MAX_RESULT;
				else res = result * tmp[2] / tmp[0];
				break;
			default:
				break;
			}
			break;
		}
						// Needed to make sure there is no fractions or division by 0
						// In case that happends res will be set so it will return "wrong answer"
		case Sign::DIV:{
			switch (OpSign2)
			{
			case Sign::MINUS:
				if ((result + tmp[2]) % tmp[0] != 0) res = MAX_RESULT;
				else res = (result + tmp[2]) / tmp[0];
				break;
			case Sign::PLUS:
				if ((result - tmp[2]) % tmp[0] != 0) res = MAX_RESULT;
				else res = (result - tmp[2]) / tmp[0];
				break;
			case Sign::MULT:
				if (tmp[0] % (result / tmp[2]) != 0) res = MAX_RESULT;
				else res = tmp[0] % (result / tmp[2]);
				break;
			case Sign::DIV:
				if (tmp[0] % (result / tmp[2]) != 0) res = MAX_RESULT;
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

	}

	// Case result is not in the range the number inserted by the user
	// will not solve the equation
	if (!(res < MAX_RESULT && res > 0))
		return WRONG_VALUE;

	// Case solved set hidden value2 to 0 than the next parameter inserted 
	// will be correct only in case equal to hidden value1
	hiddenValue1 = res;
	hiddenValue2 = 0;

	// Set the return value to be waiting for second parameter
	is_solved = WAIT_FOR_SECOND_PARAM;

	return is_solved;
}