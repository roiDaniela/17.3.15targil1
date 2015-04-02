//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ScreenData.h
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

#ifndef _SCREENDATA_H_
#define _SCREENDATA_H_

#include <map>
#include "Point.h"
using namespace std;
class ScreenData
{

private:
	map<Point, int  > PointsData;
	
public:
	bool isPointNearOrInsideOtherPoint(Point* p);
	bool is_point_exist(const Point& ptPoint)const ;
	bool insert_point(const Point& ptPoint, const int value);
	bool remove_point(Point& ptPoint );
	bool is_number_exist(const int value);
	int GetElementByPoint(const Point& ptPoint) ;
	void clear_data();
	//~ScreenData();
};

#endif