//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ScreenData.cpp
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

#include "ScreenData.h"

bool ScreenData::is_point_exist(const Point& ptPoint)
{
	unsigned int x, y;

	for (std::list<Point>::iterator curr_point = Data.begin(); curr_point != Data.end(); ++curr_point)
		if (true)
			return true;
	return false;
}

void ScreenData::insert_point(const Point& ptPoint)
{
	Data.push_back(ptPoint);
}

void ScreenData::clear_data(){
	Data.clear();
}
