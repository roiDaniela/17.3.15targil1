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
			  value != PLAYER2_SIGN   &&
			  value != SHOOT_SIGN	  &&
			  value != ROWFLYERS_SIGN &&
			  value != NUM_EATERS_SIGN )
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
		int tmpValue = GetElementByPoint(ptPoint);
		if (tmpValue > TWO_DIGIT_VALUE &&
			tmpValue != PLAYER1_SIGN   &&
			tmpValue != PLAYER2_SIGN   /*&&
			tmpValue != SHOOT_SIGN	  &&
			tmpValue != ROWFLYERS_SIGN &&
			tmpValue != NUM_EATERS_SIGN*/){
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

//---------------------------------------------------------------------------------------
// this function get the nearest point
//---------------------------------------------------------------------------------------
Point ScreenData::GetNearestPoint(const Point& ptLocation, int Distance){
	for (int i = 0; i < Distance; ++i) {
		Point p[4] = {
			// let's assume Point c'tor fix x,y that are outside of
			// screen borders to the correct place inside screen borders
			Point((ptLocation.getX() - i) % LENGH_OF_LINE, (ptLocation.getY() + i - Distance) % LENGH_OF_PAGE),
			Point((ptLocation.getX() + i) % LENGH_OF_LINE, (ptLocation.getY() - i + Distance) % LENGH_OF_PAGE),
			Point((ptLocation.getX() - i + Distance) % LENGH_OF_LINE, (ptLocation.getY() + i) % LENGH_OF_PAGE),
			Point((ptLocation.getX() + i - Distance) % LENGH_OF_LINE, (ptLocation.getY() - i) % LENGH_OF_PAGE) };
		
		for (int j = 0; j < 4 ; ++j ) {
			int tmp = GetElementByPoint(p[j]);
			if (tmp != VALUE_NOT_FOUND && !IsValueACreature(tmp) && tmp != NUM_EATERS_SIGN )
				return p[j];
		}
	}
	return ptLocation/*Point(0,0)*/;
}

//---------------------------------------------------------------------------------------
// this function gets the nearest point
//---------------------------------------------------------------------------------------
Point ScreenData::GetNearestPoint(const Point& PtLocation){
	// If the screen has more then half full than each coordinate is 
	// more then 50% set so then ring search is more efficient
	static const int RING_SEARCH = ((LENGH_OF_LINE/*80*/ / 2) * (LENGH_OF_PAGE /*24*/ - 4)) / 2;
	if (PointsData.size() <= RING_SEARCH )
		return GetNearestPointByGeneralSearch(PtLocation);
	return GetNearestPointByRingSearch(PtLocation, /*80*/LENGH_OF_LINE);
}

//---------------------------------------------------------------------------------------
// this function get the nearest point by ring search
//---------------------------------------------------------------------------------------
Point ScreenData::GetNearestPointByRingSearch(const Point& PtLocation, const int RingSize ){
		for (int i = 1; i<RingSize; ++i) {
			Point ptTmp = GetNearestPoint(PtLocation, i);
			if (ptTmp!=PtLocation/*Point(0,0)*/) 
				return ptTmp;
		}
		return PtLocation/*Point(0,0)*/;
}

//---------------------------------------------------------------------------------------
// this function get the nearest point by generak search
//---------------------------------------------------------------------------------------
Point ScreenData::GetNearestPointByGeneralSearch(const Point& PtLocation){
	int tmpDistance = 300;
	Point* tmpPoint = new Point(PtLocation);
	for (std::map<Point,int>::iterator cIter  = PointsData.begin(); cIter != PointsData.end(); cIter++){
		int tmp = 0;
		if (!IsValueACreature(cIter->second)){
			tmp = PtLocation.calcDistance(cIter->first, LENGH_OF_LINE, LENGH_OF_PAGE);

			if (tmp < tmpDistance){
				tmpDistance = tmp;
				tmpPoint = (Point*)&cIter->first;
			}
		}
	}

	int tmpValue = GetElementByPoint(*tmpPoint);
	
	if ( IsValueACreature(tmpValue) && tmpValue != NUM_EATERS_SIGN )
		return PtLocation/*Point(0,0)*/;


	return *tmpPoint;
}

//---------------------------------------------------------------------------------------
// this function checks if the value is a creature
//---------------------------------------------------------------------------------------
bool ScreenData::IsValueACreature( const int val ){
	return (val == PLAYER1_SIGN || val == PLAYER2_SIGN);
}