#include "TheMathGame.h"
#include <random>

void TheMathGame::startLevel(unsigned int currentLevel){
	clear_screen();
	
	gotoxy(PLAYER_1_X_POSITION,PLAYER_1_Y_POSITION);
	cout << PLAYER_1_SIGN;
	
	gotoxy(PLAYER_2_X_POSITION, PLAYER_2_Y_POSITION);
	cout << PLAYER_2_SIGN;

}
void TheMathGame::doIteration(const list<char>& keyHits){}
void TheMathGame::doSubIteration(){}
