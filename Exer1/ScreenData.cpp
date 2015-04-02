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

int ScreenData::GetElementByPoint(const Point& ptPoint){
	if (is_point_exist(ptPoint))
		return PointsData[ptPoint];
	return false;
}

const map<Point, int>& ScreenData::getData() const {
	return PointsData;
}

bool ScreenData::is_point_exist(const Point& ptPoint) const 
{
	return (!(PointsData.find(ptPoint) == PointsData.end() ));
}

bool ScreenData::insert_point(const Point& ptPoint, const int value ) 
{
	if (!is_point_exist(ptPoint)){
		PointsData[ptPoint] = value;
		return true;
	}

	return false;
}

bool ScreenData::is_number_exist(const int value){
	map<const Point, int >::iterator iter = PointsData.begin();

	while (iter != PointsData.end())
		if (iter->second == value)
			return true;
	return false;
}

///
bool ScreenData::isPointNearOrInsideOtherPoint(const Point& p ) const{
	Point pUp = Point(p.getX(), p.getY() - 1);
	Point pDown = Point(p.getX(), p.getY() + 1);
	Point pLeft = Point(p.getX() - 1, p.getY());
	Point pRight = Point(p.getX() + 1, p.getY());

	bool isPointNearOrInsideOtherPoint = (is_point_exist(p) ||
										  is_point_exist(pUp) ||
										  is_point_exist(pDown) ||
										  is_point_exist(pRight) ||
										  is_point_exist(pLeft));
	
	return isPointNearOrInsideOtherPoint;
}


void ScreenData::clear_data(){
	PointsData.clear();
}

bool ScreenData::remove_point(Point& ptPoint){
	return(PointsData.erase(PointsData.find(ptPoint)) != PointsData.end() );
}
//ScreenData::~ScreenData(){ delete[] & PointsData; }