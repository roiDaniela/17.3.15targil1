//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// TheMathGame.cpp
// -----------
// This file responsible for the logical part of the game. its realizes the exercise and moves the players.
// The 2 major methods are: startLevel, doIteration. we added other helper methods to realize the logic/ 
//
// Author: Motty Katz  && Roi Fogler
// First version: 2015-03-22
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "TheMathGame.h"

int Player::winCounter_1 = 0; //declaring statics
int Player::winCounter_2 = 0; //declaring statics
Player::Result_winner Player::winner; //declaring statics

//---------------------------------------------------------------------------------------
// this function is responsible for the option "continue" in sub menu
//---------------------------------------------------------------------------------------
void TheMathGame::resumeGame(unsigned int currentLevel){
	
	writeOnScreenLocation(Lines::LINE_ONE_LEFT, "Level Number: " + to_string(currentLevel));
	writeOnScreenLocation(Lines::LINE_TWO_LEFT, "Exercise Player 1: " + getExcercise(Player::numberOfPlayer::One).getHiddenExercise());
	writeOnScreenLocation(Lines::LINE_TWO_RIGHT, "Exercise Player 2: " + getExcercise(Player::numberOfPlayer::Two).getHiddenExercise());
	
	prepareStatusSentenceOnScreen();
	RefreshScreen(GetDB().getData(), player1.getLocationPoint(), player2.getLocationPoint());
}

//---------------------------------------------------------------------------------------
// this function gives the data base as refernce
//---------------------------------------------------------------------------------------
ScreenData& TheMathGame::GetDB(){
	return GameDB;
}

//---------------------------------------------------------------------------------------
// this function responsible to check if turn clock  over 1500 turns so level ended
//---------------------------------------------------------------------------------------
bool TheMathGame::iterationCounterIsBiggerThanAlowd() const{
	if (getIterationCounter() > TOTAL_NUMBER_OF_CLOCK_TURNS){
		CleanTopOfScreen();
		writeOnScreenLocation(Lines::LINE_ONE_MIDDLE, "Its over than 1500 turns clock!!!!!");
		writeOnScreenLocation(Lines::LINE_THREE_LEFT, "Points Player 1: " + to_string(player1.getWinCounter()));
		writeOnScreenLocation(Lines::LINE_THREE_RIGHT, "Points Player 2: " + to_string(player2.getWinCounter()));
		Sleep(1500);
		return true;
	}

	return false;
}

//---------------------------------------------------------------------------------------
// init params for level begining
//---------------------------------------------------------------------------------------
void TheMathGame::initParams(int currentLevel){
	iterationCounter = 0;
	player1.setIsWin(false);
	player1.setLocationPoint(Player::PLAYER_1_X_POSITION, Player::PLAYER_1_Y_POSITION);
	player1.initErrorCounter();
	
	player2.setIsWin(false);
	player2.setLocationPoint(Player::PLAYER_2_X_POSITION, Player::PLAYER_2_Y_POSITION);
	player2.initErrorCounter();
	if (currentLevel == 1){
		player1.updateWinCounter(true);
		player2.updateWinCounter(true);
	}
	GameDB.clear_data();
}

//---------------------------------------------------------------------------------------
// major method: at the begining of the level
//---------------------------------------------------------------------------------------
void TheMathGame::startLevel(unsigned int currentLevel){
	initParams(currentLevel);

	// Clean the screen
	clear_screen();

	// Init two players as stay
	player1.setDirection(Direction::RIGHT);
	player2.setDirection(Direction::LEFT);

	setExercise(player1.getPlayerNumber(), currentLevel);
	setExercise(player2.getPlayerNumber(), currentLevel);

	// Create exercise
	writeOnScreenLocation(Lines::LINE_ONE_LEFT, "Level Number: " + to_string(currentLevel));
	writeOnScreenLocation(Lines::LINE_TWO_LEFT, "Exercise Player 1: " + getExcercise(Player::numberOfPlayer::One).getHiddenExercise());
	writeOnScreenLocation(Lines::LINE_TWO_RIGHT, "Exercise Player 2: " + getExcercise(Player::numberOfPlayer::Two).getHiddenExercise());

	// Init the DB with the initial points of the players
	GameDB.insert_point(player1.getLocationPoint(), player1.PLAYER_1_SIGN);
	GameDB.insert_point(player2.getLocationPoint(), player2.PLAYER_2_SIGN);
}

//---------------------------------------------------------------------------------------
// this function prints messages to user and situation of the game in the first rows
// at the beginig of the level
//---------------------------------------------------------------------------------------
void TheMathGame::prepareStatusSentenceOnScreen(){
	int playerErrors;
	string sentence = "Player 1 Life Errors: ";
	playerErrors = (TOTAL_NUMBER_OF_ERRORS - player1.getErrorCounter());
	for (int i = 0; i < playerErrors; i++)
	{
		sentence += "*";
	}
	sentence += " Points:" + to_string(player1.getWinCounter());

	writeOnScreenLocation(Lines::LINE_THREE_LEFT, sentence);

	sentence = "Player 2 Life Errors: ";
	playerErrors = (TOTAL_NUMBER_OF_ERRORS - player2.getErrorCounter());
	for (int i = 0; i < playerErrors; i++)
	{
		sentence += "*";
	}
	sentence += " Points:" + to_string(player2.getWinCounter());

	writeOnScreenLocation(Lines::LINE_THREE_RIGHT, sentence);
}

//---------------------------------------------------------------------------------------
// this method responsible on the itaertion in curr level, one of two major 
// methods of the class 
//---------------------------------------------------------------------------------------
void TheMathGame::doIteration(const list<char>& keyHits, unsigned int currentLevel){
	prepareStatusSentenceOnScreen();
	
	// Check its not over than 1500 turns
	UpdateIterationCounter();

	// pass over the keyHits in order to collect the players input
	for (list<char>::const_iterator itr = keyHits.cbegin();
		itr != keyHits.cend();
		++itr)
	{
		Player::MOVE_KEYS_PLAYER curr_input = static_cast<Player::MOVE_KEYS_PLAYER>(*itr);

		setPlayerDirectionByKeyValue(curr_input);
	}

	// Check the next location of players: in case they will meet set them as 'stay' otherwise set their 
	// direction
	if (player1.getNextLocation(player1.getDirection()) == player2.getNextLocation(player2.getDirection())){
		
		if (player1.getNextLocation(player1.getDirection()) != player2.getLocationPoint() ){
			GameDB.remove_point(player1.getLocationPoint());
			player1.move(player1.getDirection());
		}
		if (player2.getNextLocation(player2.getDirection()) != player1.getLocationPoint()){
			GameDB.remove_point(player2.getLocationPoint());
			player2.move(player2.getDirection());
		}

		player1.setDirection(Direction::STAY); 
		player2.setDirection(Direction::STAY); 
	}
	else{
		GameDB.remove_point(player1.getLocationPoint());
		player1.move(player1.getDirection());
		GameDB.remove_point(player2.getLocationPoint());
		player2.move(player2.getDirection());
	}	

	//check if won
	if (GameDB.GetElementByPoint(player1.getLocationPoint()) == getExcercise(player1.getPlayerNumber()).getHiddenValue()){
		player1.setIsWin(true);
		setGameWinner();
	}
	else if (GameDB.GetElementByPoint(player2.getLocationPoint()) == getExcercise(player2.getPlayerNumber()).getHiddenValue()){
		player2.setIsWin(true);
		setGameWinner();
	}
	else
	{
		// Case its player1 wrong catch
		// check if in the if condition GameDB.GetElementByPoint(player2.getLocationPoint()) != Player::PLAYER_2_SIGN is needed
		if (GameDB.GetElementByPoint(player1.getLocationPoint()) != ScreenData::VALUE_NOT_FOUND &&
			GameDB.GetElementByPoint(player1.getLocationPoint()) != Player::PLAYER_1_SIGN){
			player1.addToErrorCounter();
			
			// case 2 digits number delete from screen the second digit
			if (GameDB.GetElementByPoint(player1.getLocationPoint()) > ScreenData::TOW_DIGIT_VALUE){
				gotoxy(player1.getLocationPoint().getX() + 1, player1.getLocationPoint().getY());
				cout << " ";
				gotoxy(player1.getLocationPoint().getX() - 1, player1.getLocationPoint().getY());
				cout << " ";
			}
			// Delete from DB = the reason i decided that mathGame shoud delete is that i don't want
			// Player class will get the db as a reference at all
			GameDB.remove_point(player1.getLocationPoint());
		}
		
		// Case its player2 wrong catch
		// check if in the if condition GameDB.GetElementByPoint(player2.getLocationPoint()) != Player::PLAYER_2_SIGN is needed
		if (GameDB.GetElementByPoint(player2.getLocationPoint()) != ScreenData::VALUE_NOT_FOUND &&
		    GameDB.GetElementByPoint(player2.getLocationPoint()) != Player::PLAYER_2_SIGN){
					player2.addToErrorCounter();

			// case 2 digits number delete from screen the second digit
			if (GameDB.GetElementByPoint(player2.getLocationPoint()) > ScreenData::TOW_DIGIT_VALUE){
				gotoxy(player2.getLocationPoint().getX() + 1, player2.getLocationPoint().getY());
				cout << " ";
				gotoxy(player2.getLocationPoint().getX() - 1, player2.getLocationPoint().getY());
				cout << " ";
			}

			// Delete from DB = the reason i decided that mathGame shoud delete is that i don't want
			// Player class will get the db as a reference at all
			GameDB.remove_point(player2.getLocationPoint());
		}

		GameDB.insert_point(player1.getLocationPoint(), Player::PLAYER_1_SIGN); 
		GameDB.insert_point(player2.getLocationPoint(), Player::PLAYER_2_SIGN);

		// case error point exceeded its range delete player from DB
		if (player1.getErrorCounter() == Player::MAX_ERROR_FOR_MATH_GAME){
			GameDB.remove_point(player1.getLocationPoint());
			player1.setDirection(Direction::STAY); // Set player as stay
			gotoxy(player1.getLocationPoint());
			cout << " "; // Delete the player from screen
			player1.setLocationPoint(NULL, NULL); // won't be exist when checking if a crush happend
		}
		if (player2.getErrorCounter() == Player::MAX_ERROR_FOR_MATH_GAME) {
			GameDB.remove_point(player2.getLocationPoint());
			player2.setDirection(Direction::STAY); // Set player as stay
			gotoxy(player2.getLocationPoint());
			cout << " "; // Delete the player from screen
			player2.setLocationPoint(NULL, NULL); // won't be exist when checking if a crush happend
		}

		// Do it just 1 time at 5 iterations
		if (getIterationCounter() % 5 == 0){
			// Add random number to screen
			unsigned int value = RandomOutput::CreateRandomValue(10 + currentLevel);
			int numOfDigits = (value > ScreenData::TOW_DIGIT_VALUE) ? 2 : 1;
			Point* ptTmp = RandomOutput::CreateRandomPoint(GameDB, numOfDigits);
			if (ptTmp != NULL){
				gotoxy(*ptTmp);
				cout << value;
				GameDB.insert_point(*ptTmp, value);
				delete ptTmp;
			}
		}
	}
}

void TheMathGame::doSubIteration(unsigned int currentLevel){
}

//---------------------------------------------------------------------------------------
// this function gets a direction as param and move the suit player  
//---------------------------------------------------------------------------------------
void TheMathGame::setPlayerDirectionByKeyValue(Player::MOVE_KEYS_PLAYER curr_input){

	switch (curr_input){
	case Player::PLAYER_1_DOWN:{
		if (player1.getErrorCounter() < Player::MAX_ERROR_FOR_MATH_GAME){
			player1.setDirection(Direction::DOWN);
		}

		break;
	}
	case Player::PLAYER_1_UP:{
		if (player1.getErrorCounter() < Player::MAX_ERROR_FOR_MATH_GAME){
			player1.setDirection(Direction::UP);
		}

		break;
	}
	case Player::PLAYER_1_LEFT:{
		if (player1.getErrorCounter() < Player::MAX_ERROR_FOR_MATH_GAME){
			player1.setDirection(Direction::LEFT);
		}

		break;
	}
	case Player::PLAYER_1_RIGHT:{
		if (player1.getErrorCounter() < Player::MAX_ERROR_FOR_MATH_GAME){
			player1.setDirection(Direction::RIGHT);
		}

		break;
	}
	case Player::PLAYER_2_DOWN:{
		if (player2.getErrorCounter() < Player::MAX_ERROR_FOR_MATH_GAME){
			player2.setDirection(Direction::DOWN);
		}

		break;
	}
	case Player::PLAYER_2_LEFT:{
		if (player2.getErrorCounter() < Player::MAX_ERROR_FOR_MATH_GAME){
			player2.setDirection(Direction::LEFT);
		}

		break;
	}
	case Player::PLAYER_2_RIGHT:{
		if (player2.getErrorCounter() < Player::MAX_ERROR_FOR_MATH_GAME){
			player2.setDirection(Direction::RIGHT);
		}

		break;
	}
	case Player::PLAYER_2_UP:{
		if (player2.getErrorCounter() < Player::MAX_ERROR_FOR_MATH_GAME){
			player2.setDirection(Direction::UP);
		}

		break;
	}
	default:{
		break;
	}
	}
}
