#include "TheMathGame.h"
#include "Player.h"

void TheMathGame::startLevel(unsigned int currentLevel){
	// Clean the screen
	clear_screen();
	
	// Create exercise
	CreateExercise exercise(currentLevel);
	correctNumber = exercise.getHiddenValue();
	writeOnTopOfScreen(exercise.getHiddenExercise());

	Player* p1 = new Player(Player::numberOfPlayer::One);
	Player* p2 = new Player(Player::numberOfPlayer::Two);

	p1->printSighn();
	p2->printSighn();
	// Print the players
	/*gotoxy(PLAYER_1_X_POSITION,PLAYER_1_Y_POSITION);
	cout << PLAYER_1_SIGN;
	
	gotoxy(PLAYER_2_X_POSITION, PLAYER_2_Y_POSITION);
	cout << PLAYER_2_SIGN;*/
}
void TheMathGame::doIteration(const list<char>& keyHits){}
void TheMathGame::doSubIteration(){}
