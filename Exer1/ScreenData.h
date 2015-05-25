//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ScreenData.h
// -----------
// This file is the DATA BASE of the game. its saves all locations and values on the screen.
// it uses "map" instead of 2 large matrix (mat[80][24]) in order to save memory.
//
// Author: Motty Katz  && Roi Fogler
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _SCREENDATA_H_
#define _SCREENDATA_H_

#include <map>
#include "io_utils.h"
#include "Point.h"
#include <math.h>
using namespace std;
class ScreenData
{

private:
	map<Point, int  > PointsData;
	Point* GetNearestPointByRingSearch(const Point& PtLocation, const int RingSize);
	Point* GetNearestPointByGeneralSearch(const Point& PtLocation);
	Point* GetNearestPoint(const Point& ptLocation, int Distance );
	bool IsValueACreature(const int value);
public:
	enum DBErrMsg{ VALUE_NOT_FOUND = -1, 
				   TWO_DIGIT_VALUE = 9, 
				   PLAYER1_SIGN = '@', 
				   PLAYER2_SIGN = '#', 
				   SHOOT_SIGN = '*', 
				   ROWFLYERS_SIGN = '!',
				   NUM_EATERS_SIGN = '%' };
	const map<Point, int>& getData() const;
	bool isPointNearOrInsideOtherPoint(const Point& p, const int NumOfDigits );
	bool is_point_exist(const Point& ptPoint);
	bool insert_point(const Point& ptPoint, const int value);
	bool remove_point(const Point& ptPoint);
	bool is_number_exist(const int value);
	int GetElementByPoint(const Point& ptPoint);
	void clear_data();
	Point* GetNearestPoint(const Point& PtLocation);
};

#endif