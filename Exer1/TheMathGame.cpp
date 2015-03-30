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

	// 
}
void TheMathGame::doIteration(const list<char>& keyHits){
	// pass over the keyHits in order to collect the players input
	for (list<char>::const_iterator itr = keyHits.cbegin(); 
		itr != keyHits.cend(); 
		++itr)
	{
		Player::MOVE_KEYS_PLAYER curr_input = static_cast<Player::MOVE_KEYS_PLAYER>(*itr);
		
		setPlayerDirectionByKeyValue(curr_input);
	}

	player1->move(player1->getDirection());
	player2->move(player2->getDirection());
	
	// if someone wone - need to delete players pointer
	
	GameDB.insert_point(player1->getLocationPoint(), Player::PLAYER_1_SIGN);
	GameDB.insert_point(player2->getLocationPoint(), Player::PLAYER_2_SIGN);
	GameDB.insert_point(RandomOutput::CreateRandomPoint(&GameDB), RandomOutput::CreateRandomValue(CurrentLevel));
}

void TheMathGame::doSubIteration(){ 
	
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
