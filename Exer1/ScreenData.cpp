//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ScreenData.cpp
// -----------
// This file is the DATA BASE of the game. its saves all locations and values on the screen.
// it uses "map" instead of 2 large matrix (mat[80][24]) in order to save memory.
//
// Author: Motty Katz  && Roi Fogler
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "ScreenData.h"

//---------------------------------------------------------------------------------------
// this function gets a point and return the elemeny inside the point
//---------------------------------------------------------------------------------------
int ScreenData::GetElementByPoint(const Point& ptPoint){
	if (is_point_exist(ptPoint))
		return PointsData[ptPoint];
	return DBErrMsg::VALUE_NOT_FOUND;
}

//---------------------------------------------------------------------------------------
// this function gives the array of points
//---------------------------------------------------------------------------------------
const map<Point, int>& ScreenData::getData() const {
	return PointsData;
}

//---------------------------------------------------------------------------------------
// this function checks if that point is inside the data base
//---------------------------------------------------------------------------------------
bool ScreenData::is_point_exist(const Point& ptPoint)
{
	return (!(PointsData.find(ptPoint) == PointsData.end()));
}

//---------------------------------------------------------------------------------------
// this function gets value & point and saves in the db (value, location) 
//---------------------------------------------------------------------------------------
bool ScreenData::insert_point(const Point& ptPoint, const int value)
{
	if (!(is_point_exist(ptPoint))){
		PointsData[ptPoint] = value;
		if (  value > DBErrMsg::TOW_DIGIT_VALUE && 
			  value != DBErrMsg::PLAYER1_SIGN   &&
			  value != DBErrMsg::PLAYER2_SIGN  )
			PointsData[Point(ptPoint.getX() + 1, ptPoint.getY())] = value;
		return true;
	}

	return false;
}

//---------------------------------------------------------------------------------------
// this function checks if number is inside the db
//---------------------------------------------------------------------------------------
bool ScreenData::is_number_exist(const int value){
	map<const Point, int >::iterator iter = PointsData.begin();

	while (iter != PointsData.end())
		if (iter->second == value)
			return true;
	return false;
}

//---------------------------------------------------------------------------------------
// this function checks if the pointn is in legal location for a new random point
//---------------------------------------------------------------------------------------
bool ScreenData::isPointNearOrInsideOtherPoint(const Point& p, const int numOfDigits){
	// Get all "problematic locations"
	Point pUp = Point(p.getX(), p.getY() - 1);
	Point pDown = Point(p.getX(), p.getY() + 1);
	Point pLeft = (GetElementByPoint(Point(p.getX() - 1, p.getY())) == VALUE_NOT_FOUND &&
				    GetElementByPoint(Point(p.getX() - 2, p.getY())) > 9 )? 
				  (Point(p.getX() - 2, p.getY())) : (Point(p.getX() - 1, p.getY()));
	Point pRight = Point(p.getX() + 1, p.getY());
	Point pRightByDigits = Point(p.getX() + numOfDigits, p.getY());

	// check if the problematic locations exists
	bool isPointNearOrInsideOtherPoint = (is_point_exist(p) ||
		is_point_exist(pUp) ||
		is_point_exist(pDown) ||
		is_point_exist(pRight) ||
		is_point_exist(pRightByDigits)||
		is_point_exist(pLeft));

	return isPointNearOrInsideOtherPoint;
}

//---------------------------------------------------------------------------------------
// this function cleans the db
//---------------------------------------------------------------------------------------
void ScreenData::clear_data(){
	PointsData.clear();
}

//---------------------------------------------------------------------------------------
// this function gets a point and clean the location from the db
//---------------------------------------------------------------------------------------
bool ScreenData::remove_point(const Point& ptPoint){
	bool tmp;
	if (is_point_exist(ptPoint)){
		if (GetElementByPoint(ptPoint) > TOW_DIGIT_VALUE &&
			GetElementByPoint(ptPoint) != PLAYER1_SIGN   &&
			GetElementByPoint(ptPoint) != PLAYER2_SIGN){
			if (PointsData.find(Point(ptPoint.getX() + 1, ptPoint.getY()))!= PointsData.end())
				tmp = PointsData.erase(Point(ptPoint.getX() + 1, ptPoint.getY()));// ||
			else 
				tmp = PointsData.erase(Point(ptPoint.getX() - 1, ptPoint.getY()));// ||
			tmp = PointsData.erase(PointsData.find(ptPoint)) != PointsData.end();
			return tmp;
		}
		else
			return(PointsData.erase(PointsData.find(ptPoint)) != PointsData.end());
	}
	return false;
}
