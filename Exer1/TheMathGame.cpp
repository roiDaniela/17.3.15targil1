#include "TheMathGame.h"
#include "Player.h"

void TheMathGame::startLevel(unsigned int currentLevel){
	

	// Clean the screen
	clear_screen();
	
	// Create exercise
	CreateExercise exercise(currentLevel);
	correctNumber = exercise.getHiddenValue();
	writeOnTopOfScreen("******** The exercise is: " + exercise.getHiddenExercise());
	
	// Init two players as stay
	player1 = new Player(Player::numberOfPlayer::One, Direction::RIGHT);
	player2 = new Player(Player::numberOfPlayer::Two, Direction::LEFT);

	// Init the DB with the initial points of the players
	GameDB.insert_point(player1->getLocationPoint(), player1->PLAYER_1_SIGN);
	GameDB.insert_point(player2->getLocationPoint(), player2->PLAYER_2_SIGN);
}
void TheMathGame::doIteration(const list<char>& keyHits, unsigned int currentLevel){
	// pass over the keyHits in order to collect the players input
	for (list<char>::const_iterator itr = keyHits.cbegin(); 
		itr != keyHits.cend(); 
		++itr)
	{
		Player::MOVE_KEYS_PLAYER curr_input = static_cast<Player::MOVE_KEYS_PLAYER>(*itr);
		
		setPlayerDirectionByKeyValue(curr_input);
	}


	// Delete player location from DB before movement and insert the new point to DB
	GameDB.remove_point(player1->getLocationPoint());
	player1->move(player1->getDirection());


	GameDB.remove_point(player2->getLocationPoint());
	player2->move(player2->getDirection());
	
	//check if won
	if (GameDB.GetElementByPoint(player1->getLocationPoint()) == correctNumber){
		player1->setIsWin(true);
	}
	else if (GameDB.GetElementByPoint(player1->getLocationPoint()) == correctNumber){
		player2->setIsWin(true);
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
