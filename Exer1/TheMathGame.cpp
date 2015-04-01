#include "TheMathGame.h"

int Player::winCounter_1; //declaring statics
int Player::winCounter_2; //declaring statics
Player::Result_winner Player::winner; //declaring statics

void TheMathGame::startLevel(unsigned int currentLevel){
	initIterationCounter();

	// Clean the screen
	clear_screen();
	
	// Create exercise
	CreateExercise exercise_1(currentLevel);
	CreateExercise exercise_2(currentLevel);
	correctNumber_1 = exercise_1.getHiddenValue();
	correctNumber_2 = exercise_2.getHiddenValue();
	writeOnScreenLocation(Lines::LINE_ONE_RIGHT, "Level Number: " + to_string(currentLevel));
	writeOnScreenLocation(Lines::LINE_TWO_RIGHT, "Exercise Player 1: " + exercise_1.getHiddenExercise());
	writeOnScreenLocation(Lines::LINE_TWO_LEFT, "Exercise Player 2: " + exercise_2.getHiddenExercise());
	
	// Init two players as stay
	player1 = new Player(Player::numberOfPlayer::One, Direction::RIGHT);
	player2 = new Player(Player::numberOfPlayer::Two, Direction::LEFT);

	// Init the DB with the initial points of the players
	GameDB.insert_point(player1->getLocationPoint(), player1->PLAYER_1_SIGN);
	GameDB.insert_point(player2->getLocationPoint(), player2->PLAYER_2_SIGN);
}

void TheMathGame::prepareStatusSentenceOnScreen(){
	int playerErrors;
	string sentence = "Player 1 Life Errors: ";
	playerErrors = (TOTAL_NUMBER_OF_ERRORS - player1->getErrorCounter());
	for (int i = 0; i < playerErrors; i++)
	{
		sentence += "*";
	}
	sentence += " Points:" + to_string(player1->getWinCounter());

	writeOnScreenLocation(Lines::LINE_THREE_RIGHT, sentence);
	
	sentence = "Player 2 Life Errors: ";
	playerErrors = (TOTAL_NUMBER_OF_ERRORS - player2->getErrorCounter());
	for (int i = 0; i < playerErrors; i++)
	{
		sentence += "*";
	}
	sentence += " Points:" + to_string(player2->getWinCounter());

	writeOnScreenLocation(Lines::LINE_THREE_LEFT, sentence);

	setWinner();
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
	if ((!(player1->getLocationPoint().IsPointsAdjacent(player2->getLocationPoint()))) ||
		player1->getNextLocation(player1->getDirection()) != player2->getLocationPoint() ){
		GameDB.remove_point(player1->getLocationPoint());
		player1->move(player1->getDirection());
	}
	else
		player1->setDirection(Direction::STAY);
	
	// Delete player2 location from DB before movement and insert the new point to DB
	// only in case points are not adjacent	else player won't move
	if ((!(player2->getLocationPoint().IsPointsAdjacent(player1->getLocationPoint()))) ||
		player2->getNextLocation(player2->getDirection()) != player1->getLocationPoint()){
		GameDB.remove_point(player2->getLocationPoint());
		player2->move(player2->getDirection());
	}
	else
		player2->setDirection(Direction::STAY);


	//check if won
	if (GameDB.GetElementByPoint(player1->getLocationPoint()) == correctNumber_1){
		player1->setIsWin(true);
		player1->updateWinCounter();
	}
	else if (GameDB.GetElementByPoint(player2->getLocationPoint()) == correctNumber_2){
		player2->setIsWin(true);
		player2->updateWinCounter();
	}
	else
	{
		GameDB.insert_point(player1->getLocationPoint(), Player::PLAYER_1_SIGN);
		GameDB.insert_point(player2->getLocationPoint(), Player::PLAYER_2_SIGN);

		// Add random number to screen
		Point ptTmp(RandomOutput::CreateRandomPoint());
		
		unsigned int value = RandomOutput::CreateRandomValue(10 + currentLevel);
		while (!GameDB.insert_point(ptTmp, value))
			ptTmp = RandomOutput::CreateRandomPoint();

		gotoxy(ptTmp.getX(), ptTmp.getY());
		cout << GameDB.GetElementByPoint(ptTmp);
	}

}

void TheMathGame::doSubIteration(unsigned int currentLevel){
}

void TheMathGame::setPlayerDirectionByKeyValue(Player::MOVE_KEYS_PLAYER curr_input){
	switch (curr_input){
		case Player::MOVE_KEYS_PLAYER::PLAYER_1_DOWN:{
			player1->setDirection(Direction::DOWN);

			break;
		}
		case Player::MOVE_KEYS_PLAYER::PLAYER_1_UP:{
			player1->setDirection(Direction::UP);

			break;
		}
		case Player::MOVE_KEYS_PLAYER::PLAYER_1_LEFT:{
			player1->setDirection(Direction::LEFT);

			break;
		}
		case Player::MOVE_KEYS_PLAYER::PLAYER_1_RIGHT:{
			player1->setDirection(Direction::RIGHT);

			break;
		}
		case Player::MOVE_KEYS_PLAYER::PLAYER_2_DOWN:{
			player2->setDirection(Direction::DOWN);

			break;
		}
		case Player::MOVE_KEYS_PLAYER::PLAYER_2_LEFT:{
			player2->setDirection(Direction::LEFT);

			break;
		}
		case Player::MOVE_KEYS_PLAYER::PLAYER_2_RIGHT:{
			player2->setDirection(Direction::RIGHT);

			break;
		}
		case Player::MOVE_KEYS_PLAYER::PLAYER_2_UP:{
			player2->setDirection(Direction::UP);

			break;
		}
		default:{
			break;
		}
	}
}
