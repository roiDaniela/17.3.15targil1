//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Player.cpp
// -----------
// This file is responsible to the new type = player: players in the game. here we set the players locations. signs and moves
// All the data on the players should be on this member.
//
// Author: Motty Katz  && Roi Fogler
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "Player.h"

//---------------------------------------------------------------------------------------
// Ctor
//---------------------------------------------------------------------------------------
Player::Player(Player::numberOfPlayer number, int currIteration, Direction::value d) : playerNumber(number),
																	prevDirection(d),
																	winCounter(0),
																	shootCounter(5),
																	errorCounter(0),
																	Creature((number == One) ? Point(PLAYER_1_X_POSITION, PLAYER_1_Y_POSITION) : 
													                                           Point(PLAYER_2_X_POSITION, PLAYER_2_Y_POSITION), d){
	// Move by inited directions
	move(currIteration);
}

//---------------------------------------------------------------------------------------
// this method uses the player to shoot
//---------------------------------------------------------------------------------------
bool Player::shoot(){
	if (shootCounter > 0){
		lessShootCounter();
		return true;
	}
	
	return false;
}

//---------------------------------------------------------------------------------------
// this method prints the player sign
//---------------------------------------------------------------------------------------
void Player::printSighn(){
	gotoxy(getLocationPoint());
	(playerNumber == One) ? cout << PLAYER_1_SIGN : cout << PLAYER_2_SIGN;
}