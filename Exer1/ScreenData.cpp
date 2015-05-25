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
		if (  value > TWO_DIGIT_VALUE && 
			  value != PLAYER1_SIGN   &&
			  value != PLAYER2_SIGN /*&&
			  value != SHOOT_SIGN*/)
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
		if (GetElementByPoint(ptPoint) > TWO_DIGIT_VALUE &&
			GetElementByPoint(ptPoint) != PLAYER1_SIGN   &&
			GetElementByPoint(ptPoint) != PLAYER2_SIGN){
			if (PointsData.find(Point(ptPoint.getX() + 1, ptPoint.getY())) != PointsData.end()){
				tmp = PointsData.erase(Point(ptPoint.getX() + 1, ptPoint.getY()));// ||
			}
			else{
				tmp = PointsData.erase(Point(ptPoint.getX() - 1, ptPoint.getY()));// ||
			}
			tmp = PointsData.erase(PointsData.find(ptPoint)) != PointsData.end();
			return tmp;
		}
		else
			return(PointsData.erase(PointsData.find(ptPoint)) != PointsData.end());
	}
	return false;
}

Point* ScreenData::GetNearestPoint(const Point& ptLocation, int Distance){
	for (int i = 0; i < Distance; ++i) {
		Point p[4] = {
			// let's assume Point c'tor fix x,y that are outside of
			// screen borders to the correct place inside screen borders
			Point((ptLocation.getX() - i) % Point::X_MAX_RANGE, (ptLocation.getY() + i - Distance) % Point::Y_MAX_RANGE),
			Point((ptLocation.getX() + i) % Point::X_MAX_RANGE, (ptLocation.getY() - i + Distance) % Point::Y_MAX_RANGE),
			Point((ptLocation.getX() - i + Distance) % Point::X_MAX_RANGE, (ptLocation.getY() + i) % Point::Y_MAX_RANGE),
			Point((ptLocation.getX() + i - Distance) % Point::X_MAX_RANGE, (ptLocation.getY() - i) % Point::Y_MAX_RANGE) };
		
		for (int j = 0; j < 4 ; ++j ) {
			int tmp = GetElementByPoint(p[j]);
			if (tmp != DBErrMsg::VALUE_NOT_FOUND && tmp != DBErrMsg::PLAYER1_SIGN && tmp != DBErrMsg::PLAYER2_SIGN && tmp != DBErrMsg::SHOOT_SIGN)
				return &p[j];
		}
	}
	return NULL;

}

Point* ScreenData::GetNearestPoint(const Point& PtLocation){
	if (PointsData.size() < 100)
		return GetNearestPointByGeneralSearch(PtLocation);
	return GetNearestPointByRingSearch(PtLocation, 20);
}

Point* ScreenData::GetNearestPointByRingSearch(const Point& PtLocation, const int RingSize ){
		for (int i = 1; i<RingSize; ++i) {
			Point* ptTmp = GetNearestPoint(PtLocation, i);
			if (ptTmp) 
				return ptTmp;
		}
		return NULL;
}

Point* ScreenData::GetNearestPointByGeneralSearch(const Point& PtLocation){
	int tmpDistance = 300;
	Point* tmpPoint = new Point(0,0);
	for (std::map<Point,int>::iterator cIter  = PointsData.begin(); cIter != PointsData.end(); cIter++){
		int tmp = 0;
		if (abs(PtLocation.getX() - cIter->first.getX()) > Point::X_MAX_RANGE / 2){
			tmp += (PtLocation.getX() + cIter->first.getX()) % Point::X_MAX_RANGE;
		}
		else{
			tmp += abs(PtLocation.getX() - cIter->first.getX());
		}

		if (abs(PtLocation.getY() - cIter->first.getY()) > Point::Y_MAX_RANGE / 2){
			tmp += (PtLocation.getY() + cIter->first.getY()) % Point::Y_MAX_RANGE;
		}
		else{
			tmp += abs(PtLocation.getY() - cIter->first.getY());
		}


		if (tmp < tmpDistance){
			tmpDistance = tmp;
			tmpPoint = (Point*)&cIter->first;
		}
	}

	return tmpPoint;
}