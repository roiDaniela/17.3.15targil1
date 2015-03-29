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
	player1 = new Player(Player::numberOfPlayer::One);
	player2 = new Player(Player::numberOfPlayer::Two);

	// 
}
void TheMathGame::doIteration(const list<char>& keyHits){}
void TheMathGame::doSubIteration(){ this->player1->move(Direction::DOWN); }
