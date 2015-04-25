//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Shoot.cpp
// -----------
// This file
//
// Author: Motty Katz  && Roi Fogler
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "Shoot.h"

void Shoot::move(){
	Point targetPoint = getLocationPoint();

	// Take care all opptional directions
	switch (Shoot::getDirection())
	{
	case Direction::DOWN:{
		targetPoint = Point(getLocationPoint().getX(), getLocationPoint().getY() + 1);

		break;
	}
	case Direction::UP:{
		targetPoint = Point(getLocationPoint().getX(), getLocationPoint().getY() - 1);

		break;
	}
	case Direction::RIGHT:{
		targetPoint = Point(getLocationPoint().getX() + 1, getLocationPoint().getY());

		break;
	}
	case Direction::LEFT:{
		targetPoint = Point(getLocationPoint().getX() - 1, getLocationPoint().getY());

		break;
	}
	default:{ // STAY

		break;
	}
	}

	// Case it was not STAY
	if (Shoot::getDirection() != Direction::STAY){

		// Needs to be cyclic: take care that screen size is (24 X 80)
		if (getDirection() == Direction::RIGHT){
			targetPoint.setX(targetPoint.getX() % LENGH_OF_LINE);
		}
		else if (getDirection() == Direction::LEFT && targetPoint.getX() == -1){
			targetPoint.setX(LENGH_OF_LINE - 1);
		}


		if ((getDirection() == Direction::DOWN) && (targetPoint.getY() > LENGH_OF_PAGE)){
			targetPoint.setY((targetPoint.getY() % LENGH_OF_PAGE) + AMOUNT_OF_INSTRUCTIONS_LINE);
		}
		else if ((getDirection() == Direction::UP) && (targetPoint.getY() <= AMOUNT_OF_INSTRUCTIONS_LINE)){
			targetPoint.setY(LENGH_OF_PAGE - (targetPoint.getY() % AMOUNT_OF_INSTRUCTIONS_LINE));
		}

		// Delete last location
		gotoxy(getLocationPoint());
		cout << " ";

		// set new location 
		setLocationPoint(targetPoint);

		// Print new location
		printSighn();
	}
}

void Shoot::Stop(){
	setDirection(Direction::STAY);
	setShootStatus(ShootStatus::STOPPED);
	gotoxy(getLocationPoint());
	cout << " ";

}
