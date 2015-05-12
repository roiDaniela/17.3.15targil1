//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// randomOutput.cpp
// -----------
// This file represents the random output (numbers, points, signs) in the game
//
// Author: Motty Katz  && Roi Fogler
// First version: 2015-03-23
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "randomOutput.h"

//---------------------------------------------------------------------------------------
// this method gets 1 or 2 (using default parameters)params and creates random value 
// between the params 
//---------------------------------------------------------------------------------------
unsigned int RandomOutput::CreateRandomValue(unsigned int range_to, unsigned int range_from){
	return (range_from + (rand() % (range_to - range_from)));
}

//---------------------------------------------------------------------------------------
// this method gets 1 or 2 (using default parameters)params and creates random value 
// between the params 
//---------------------------------------------------------------------------------------
unsigned int RandomOutput::CreateRandomValue(unsigned int range_to, unsigned int avoidThisNumber, unsigned int range_from){
	unsigned int n = CreateRandomValue(range_to, range_from);
	
	while (n == avoidThisNumber){
		n = CreateRandomValue(range_to, range_from);
	}
	return n;
}

//---------------------------------------------------------------------------------------
// this method creates a random sign 
//---------------------------------------------------------------------------------------
Sign::Operator RandomOutput::CreateRandomSign(){

	return (Sign::Operator) CreateRandomValue(Sign::DIV, Sign::MINUS);
}

//---------------------------------------------------------------------------------------
// this method creates a random value and checks if the number is in the data base
//---------------------------------------------------------------------------------------
unsigned int RandomOutput::CreateRandomValue(ScreenData* sData, unsigned int range_to, unsigned int range_from){

	int temp = CreateRandomValue(range_to, range_from);

	while (sData->is_number_exist(temp))
		temp = CreateRandomValue(range_to, range_from);

	return temp;
}

//---------------------------------------------------------------------------------------
// this function gets a point and return the elemeny inside the point 
//---------------------------------------------------------------------------------------
Point* RandomOutput::CreateRandomPoint(ScreenData& sData, int numOfDigits){
	Point* p = new Point(CreateRandomPoint());
	bool succeded = false;
	
	// try 10 times
	for (int i = 0; i < 9 && !succeded; i++)
	{
		succeded = true;
		delete p;
		p = new Point(CreateRandomPoint());
		for (int j = 0; j < numOfDigits; j++)
		{
			succeded = (succeded && ((p->getX() + j) < LENGH_OF_LINE) && !sData.isPointNearOrInsideOtherPoint(*(p + j), numOfDigits));
		}
	}

	// if succeded return p else return null
	p = (succeded ? p : NULL);

	return p;
}
