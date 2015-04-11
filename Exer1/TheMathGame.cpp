#include "TheMathGame.h"

int Player::winCounter_1 = 0; //declaring statics
int Player::winCounter_2 = 0; //declaring statics
Player::Result_winner Player::winner; //declaring statics
//CreateExercise TheMathGame::excersisePlayer_1 = NULL; // declaring statics
//CreateExercise TheMathGame::excersisePlayer_2 = NULL; // declaring statics

void TheMathGame::resumeGame(unsigned int currentLevel){
	
	writeOnScreenLocation(Lines::LINE_ONE_LEFT, "Level Number: " + to_string(currentLevel));
	writeOnScreenLocation(Lines::LINE_TWO_LEFT, "Exercise Player 1: " + getExcercise(Player::numberOfPlayer::One).getHiddenExercise());
	writeOnScreenLocation(Lines::LINE_TWO_RIGHT, "Exercise Player 2: " + getExcercise(Player::numberOfPlayer::Two).getHiddenExercise());
	
	prepareStatusSentenceOnScreen();
	RefreshScreen(GetDB().getData(), player1.getLocationPoint(), player2.getLocationPoint());
}

ScreenData& TheMathGame::GetDB(){
	return GameDB;
}

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
	//CreateExercise exercise_1(currentLevel);
	//CreateExercise exercise_2(currentLevel);
	//correctNumber_1 = exercise_1.getHiddenValue();
	//correctNumber_2 = exercise_2.getHiddenValue();
	writeOnScreenLocation(Lines::LINE_ONE_LEFT, "Level Number: " + to_string(currentLevel));
	writeOnScreenLocation(Lines::LINE_TWO_LEFT, "Exercise Player 1: " + getExcercise(Player::numberOfPlayer::One).getHiddenExercise());
	writeOnScreenLocation(Lines::LINE_TWO_RIGHT, "Exercise Player 2: " + getExcercise(Player::numberOfPlayer::Two).getHiddenExercise());

	// Init the DB with the initial points of the players
	GameDB.insert_point(player1.getLocationPoint(), player1.PLAYER_1_SIGN);
	GameDB.insert_point(player2.getLocationPoint(), player2.PLAYER_2_SIGN);
}

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


	// Delete player1 location from DB before movement and insert the new point to DB
	// only in case points are not adjacent else player won't move
	/*if ((!(player1.getLocationPoint().IsPointsAdjacent(player2.getLocationPoint()))) ||
		( player1.getNextLocation(player1.getDirection()) != player2.getLocationPoint() &&
		  player2.getNextLocation(player2.getDirection()) != player1.getLocationPoint())){
		GameDB.remove_point(player1.getLocationPoint());
		player1.move(player1.getDirection());
	}
	else
		player1.setDirection(Direction::STAY);

	// Delete player2 location from DB before movement and insert the new point to DB
	// only in case points are not adjacent	else player won't move
	if ((!(player2.getLocationPoint().IsPointsAdjacent(player1.getLocationPoint()))) ||
		(player2.getNextLocation(player2.getDirection()) != player1.getLocationPoint() &&
		player1.getNextLocation(player1.getDirection()) != player2.getLocationPoint())){
		GameDB.remove_point(player2.getLocationPoint());
		player2.move(player2.getDirection());
	}
	else
		player2.setDirection(Direction::STAY);*/

	// Check the next location of players: in case they will meet set them as stay' otherwise set their 
	// direction
	if (player1.getNextLocation(player1.getDirection()) == player2.getNextLocation(player2.getDirection())){
		
		if (player1.getNextLocation(player1.getDirection()) != player2.getLocationPoint() ){
			GameDB.remove_point(player1.getLocationPoint());
			player1.move(player1.getDirection());
		}
		if (player2.getNextLocation(player2.getDirection()) != player1.getLocationPoint()){
			GameDB.remove_point(player2.getLocationPoint());
			player2.move(player1.getDirection());
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
		// TODO: chaeck if in the if condition GameDB.GetElementByPoint(player2.getLocationPoint()) != Player::PLAYER_2_SIGN is needed
		if (GameDB.GetElementByPoint(player1.getLocationPoint()) != ScreenData::DBErrMsg::VALUE_NOT_FOUND &&
			GameDB.GetElementByPoint(player1.getLocationPoint()) != Player::PLAYER_1_SIGN){
			player1.addToErrorCounter();
			

			int whatisIt_1 = GameDB.GetElementByPoint(player1.getLocationPoint()); // for DEBUG only
			//int whatisIt_2 = GameDB.GetElementByPoint(player2.getLocationPoint()); // for DEBUG only
			
			// Delete from DB = the reason i decided that mathGame shoud delete is that i don't want
			// Player class will get the db as a reference at all
			GameDB.remove_point(player1.getLocationPoint());
		}
		
		// Case its player2 wrong catch
		// TODO: chaeck if in the if condition GameDB.GetElementByPoint(player2.getLocationPoint()) != Player::PLAYER_2_SIGN is needed
		if (GameDB.GetElementByPoint(player2.getLocationPoint()) != ScreenData::DBErrMsg::VALUE_NOT_FOUND &&
		    GameDB.GetElementByPoint(player2.getLocationPoint()) != Player::PLAYER_2_SIGN){
					player2.addToErrorCounter();


			//int whatisIt_1 = GameDB.GetElementByPoint(player1.getLocationPoint()); // for DEBUG only
			int whatisIt_2 = GameDB.GetElementByPoint(player2.getLocationPoint()); // for DEBUG only

			// Delete from DB = the reason i decided that mathGame shoud delete is that i don't want
			// Player class will get the db as a reference at all
			GameDB.remove_point(player2.getLocationPoint());
		}

		GameDB.insert_point(player1.getLocationPoint(), Player::PLAYER_1_SIGN); 
		GameDB.insert_point(player2.getLocationPoint(), Player::PLAYER_2_SIGN);

		// case error point exceeded its range delete player from DB
		if (player1.getErrorCounter() == Player::maxErr::MAX_ERROR_FOR_MATH_GAME){
			GameDB.remove_point(player1.getLocationPoint());
			player1.setDirection(Direction::STAY); // Set player as stay
			gotoxy(player1.getLocationPoint());
			cout << " "; // Delete the player from screen
			player1.setLocationPoint(NULL, NULL); // won't be exist when checking if a crush happend
		}
		if (player2.getErrorCounter() == Player::maxErr::MAX_ERROR_FOR_MATH_GAME) {
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
			int numOfDigits = (value > 9) ? 2 : 1;
			Point* ptTmp = RandomOutput::CreateRandomPoint(GameDB, numOfDigits);
			if (ptTmp != NULL){
				Point i = *ptTmp;
				delete ptTmp;
				GameDB.insert_point(i, value);
				gotoxy(i);
				cout << GameDB.GetElementByPoint(i);
				//delete ptTmp;
			}
		}
	}
}

void TheMathGame::doSubIteration(unsigned int currentLevel){
}

void TheMathGame::setPlayerDirectionByKeyValue(Player::MOVE_KEYS_PLAYER curr_input){

	switch (curr_input){
	case Player::MOVE_KEYS_PLAYER::PLAYER_1_DOWN:{
		if (player1.getErrorCounter() < Player::maxErr::MAX_ERROR_FOR_MATH_GAME){
			player1.setDirection(Direction::DOWN);
		}

		break;
	}
	case Player::MOVE_KEYS_PLAYER::PLAYER_1_UP:{
		if (player1.getErrorCounter() < Player::maxErr::MAX_ERROR_FOR_MATH_GAME){
			player1.setDirection(Direction::UP);
		}

		break;
	}
	case Player::MOVE_KEYS_PLAYER::PLAYER_1_LEFT:{
		if (player1.getErrorCounter() < Player::maxErr::MAX_ERROR_FOR_MATH_GAME){
			player1.setDirection(Direction::LEFT);
		}

		break;
	}
	case Player::MOVE_KEYS_PLAYER::PLAYER_1_RIGHT:{
		if (player1.getErrorCounter() < Player::maxErr::MAX_ERROR_FOR_MATH_GAME){
			player1.setDirection(Direction::RIGHT);
		}

		break;
	}
	case Player::MOVE_KEYS_PLAYER::PLAYER_2_DOWN:{
		if (player2.getErrorCounter() < Player::maxErr::MAX_ERROR_FOR_MATH_GAME){
			player2.setDirection(Direction::DOWN);
		}

		break;
	}
	case Player::MOVE_KEYS_PLAYER::PLAYER_2_LEFT:{
		if (player2.getErrorCounter() < Player::maxErr::MAX_ERROR_FOR_MATH_GAME){
			player2.setDirection(Direction::LEFT);
		}

		break;
	}
	case Player::MOVE_KEYS_PLAYER::PLAYER_2_RIGHT:{
		if (player2.getErrorCounter() < Player::maxErr::MAX_ERROR_FOR_MATH_GAME){
			player2.setDirection(Direction::RIGHT);
		}

		break;
	}
	case Player::MOVE_KEYS_PLAYER::PLAYER_2_UP:{
		if (player2.getErrorCounter() < Player::maxErr::MAX_ERROR_FOR_MATH_GAME){
			player2.setDirection(Direction::UP);
		}

		break;
	}
	default:{
		break;
	}
	}
}
