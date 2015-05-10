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
	cleanShootList();
	player1.setLocationPoint(Player::PLAYER_1_X_POSITION, Player::PLAYER_1_Y_POSITION);
	player1.initErrorCounter();
	
	player2.setLocationPoint(Player::PLAYER_2_X_POSITION, Player::PLAYER_2_Y_POSITION);
	player2.initErrorCounter();
	if (currentLevel == 1){
		player1.initWinCounter();
		player2.initWinCounter();
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
	
	// Check its not over than 1500 turns and update the players itaeration
	UpdateIterationCounter();

	// pass over the keyHits in order to collect the players input
	for (list<char>::const_iterator itr = keyHits.cbegin();
		itr != keyHits.cend();
		++itr)
	{
		Player::PLAYER_KEYS curr_input = static_cast<Player::PLAYER_KEYS>(*itr);

		setKeyValues(curr_input);
	}

	// Check the next location of players: in case they will meet set them as 'stay' otherwise set their 
	// direction
	//if (player1.getNextLocation() == player2.getNextLocation()){
	//	
	//	if (player1.getNextLocation() != player2.getLocationPoint() ){
	//		GameDB.remove_point(player1.getLocationPoint());
	//		player1.move();
	//	}
	//	if (player2.getNextLocation() != player1.getLocationPoint()){
	//		GameDB.remove_point(player2.getLocationPoint());
	//		player2.move();
	//	}

	//	player1.setDirection(Direction::STAY); 
	//	player2.setDirection(Direction::STAY); 
	//}
	if (IsPlayersCrash(player1, player2)){
		HandlePlayersCrash(player1,player2);
	}
	else{
		GameDB.remove_point(player1.getLocationPoint());
		player1.move();
		GameDB.remove_point(player2.getLocationPoint());
		player2.move();
	}	
	

	CreateExercise::ExerciseErrMsg ExerMsgForPlayer1 = getExcercise(Player::One).IsProblemSolved(GameDB.GetElementByPoint(player1.getLocationPoint()));
	CreateExercise::ExerciseErrMsg ExerMsgForPlayer2 = getExcercise(Player::Two).IsProblemSolved(GameDB.GetElementByPoint(player2.getLocationPoint()));
	
	//check if won
	//if (GameDB.GetElementByPoint(player1.getLocationPoint()) == getExcercise(player1.getPlayerNumber()).getHiddenValue1()){
	if (ExerMsgForPlayer1 == CreateExercise::SOLVED){
		//player1.addToWinCounter();
		setGameWinner(player1, currentLevel);
	}
	//else if (GameDB.GetElementByPoint(player2.getLocationPoint()) == getExcercise(player2.getPlayerNumber()).getHiddenValue1()){
	else if (ExerMsgForPlayer2 == CreateExercise::SOLVED){
		setGameWinner(player2, currentLevel);
	}
	else 
	{
		// Case its player1 wrong catch
		/*// check if in the if condition GameDB.GetElementByPoint(player2.getLocationPoint()) != Player::PLAYER_2_SIGN is needed
		if (GameDB.GetElementByPoint(player1.getLocationPoint()) != ScreenData::VALUE_NOT_FOUND &&
			GameDB.GetElementByPoint(player1.getLocationPoint()) != Player::PLAYER_1_SIGN &&
			ExerMsgForPlayer1 == CreateExercise::WRONG_VALUE ){
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
		    GameDB.GetElementByPoint(player2.getLocationPoint()) != Player::PLAYER_2_SIGN &&
			ExerMsgForPlayer2 == CreateExercise::WRONG_VALUE ){
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
			GameDB.remove_point(player2.getLocationPoint());*/
			if (IsWrongCatch(player1, ExerMsgForPlayer1))
				HandleWrongCatch(player1, ExerMsgForPlayer1);
			if (IsWrongCatch(player2, ExerMsgForPlayer2))
				HandleWrongCatch(player2, ExerMsgForPlayer2);
		}
		

		GameDB.insert_point(player1.getLocationPoint(), Player::PLAYER_1_SIGN); 
		GameDB.insert_point(player2.getLocationPoint(), Player::PLAYER_2_SIGN);

		// case error point exceeded its range delete player from DB
		/*if (player1.getErrorCounter() == Player::MAX_ERROR_FOR_MATH_GAME){
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
		}*/
		if ( IsPlayerUsedAllErr(player1) )
			HandlePlayerUsedAllErr(player1);
		
		if (IsPlayerUsedAllErr(player2))
			HandlePlayerUsedAllErr(player2);

		// Do it just 1 time at 5 iterations
		if (getIterationCounter() % 5 == 0){
			// Add random number to screen
			addRandomNunberToScreen(currentLevel);
		}
}

void TheMathGame::addRandomNunberToScreen(unsigned int currentLevel){
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

void TheMathGame::doSubIteration(unsigned int currentLevel){
	//bool isShootTouched = false;
	//// Move the shoots
	//for (list<Shoot*>::iterator it = listOfShoots.begin(); it != listOfShoots.end(); it++){
	//	if (*it != NULL){
	//		if ((*it)->getNextLocation() == player1.getLocationPoint()){
	//			player1.setLocationPoint(Player::PLAYER_1_X_POSITION, Player::PLAYER_1_Y_POSITION);
	//			player1.setDirection(Direction::RIGHT);
	//			
	//			CreateExercise::ExerciseErrMsg ExerMsgForPlayer1 = getExcercise(Player::One).IsProblemSolved(GameDB.GetElementByPoint(player1.getLocationPoint()));

	//			//check if won
	//			if (ExerMsgForPlayer1 == CreateExercise::SOLVED){
	//				setGameWinner(player1, currentLevel);
	//			}

	//			isShootTouched = true;
	//		}
	//		else if ((*it)->getNextLocation() == player2.getLocationPoint()){
	//			player1.setLocationPoint(Player::PLAYER_2_X_POSITION, Player::PLAYER_2_Y_POSITION);
	//			player2.setDirection(Direction::LEFT);

	//			CreateExercise::ExerciseErrMsg ExerMsgForPlayer2 = getExcercise(Player::Two).IsProblemSolved(GameDB.GetElementByPoint(player2.getLocationPoint()));

	//			//check if won
	//			if (ExerMsgForPlayer2 == CreateExercise::SOLVED){
	//				setGameWinner(player2, currentLevel);
	//			}

	//			isShootTouched = true;
	//		}
	//		else if (GameDB.GetElementByPoint((*it)->getNextLocation()) != ScreenData::VALUE_NOT_FOUND){
	//			isShootTouched = true;
	//		}

	//		// Move
	//		GameDB.remove_point((*it)->getLocationPoint());
	//		if (!isShootTouched){
	//			(*it)->move();
	//			GameDB.insert_point((*it)->getLocationPoint(), Shoot::SHOOT_SIGN);
	//		}
	//		else{
	//			isShootTouched = false;
	//			GameDB.remove_point((*it)->getNextLocation());
	//			gotoxy((*it)->getNextLocation());
	//			cout << " ";
	//			listOfShoots.erase(it);
	//		}
	//	}
	//}
		
}

//---------------------------------------------------------------------------------------
// this function gets a direction as param and move the suit player  
//---------------------------------------------------------------------------------------
void TheMathGame::setKeyValues(Player::PLAYER_KEYS curr_input){

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
	case Player::PLAYER_1_SHOOT:{
		if (player1.getErrorCounter() < Player::MAX_ERROR_FOR_MATH_GAME){
			addShoot(player1.shoot());
		}

		break;
	}
	case Player::PLAYER_2_SHOOT:{
		if (player2.getErrorCounter() < Player::MAX_ERROR_FOR_MATH_GAME){
			addShoot(player2.shoot());
		}

		break;
	}
	default:{
		break;
	}
	}
}

// ctor
TheMathGame::TheMathGame() : excersisePlayer_1(NULL), excersisePlayer_2(NULL), player1(Player::One), player2(Player::Two), iterationCounter(0)/*, listOfShoots(NULL)*/{
	// init the array of wins
	for (int i = 0; i < 40; i++)
	{
		arrayOfWinsInLevel[i] = NO_BODY_WON;
	}
}

TheMathGame::~TheMathGame(){
	cleanShootList();
}

//---------------------------------------------------------------------------------------
// this function sets the winner in the game
//---------------------------------------------------------------------------------------
void TheMathGame::setGameWinner(Player& player, unsigned int currentLevel){
	player.addToWinCounter();
	if (player.getPlayerNumber() == Player::numberOfPlayer::One){
		setLevelResult(PLAYER_ONE_WON, currentLevel);
	}
	else if (player.getPlayerNumber() == Player::numberOfPlayer::Two){
		setLevelResult(PLAYER_TWO_WON, currentLevel);
	}
	/*else{
		setLevelResult(TIE, currentLevel);
	}*/
}

//---------------------------------------------------------------------------------------
// this function cleans the shoot list
//---------------------------------------------------------------------------------------
void TheMathGame::cleanShootList(){
		for (list<Shoot*>::iterator it = listOfShoots.begin(); it != listOfShoots.end(); it++){
		delete *it;
	}
}

//---------------------------------------------------------------------------------------
// this function update shoot counter: every 200 iterations one more shoot
//---------------------------------------------------------------------------------------
void TheMathGame::UpdateShootCounter(){
	for (int i = 1; i < getIterationCounter()/SHOOT_PER_ITERATION; i++)
	{
		player1.addToShootCounter();
		player2.addToShootCounter();
	}
}

//---------------------------------------------------------------------------------------
// this function add shoot to game
//---------------------------------------------------------------------------------------
void TheMathGame::addShoot(Shoot* s){
	if (s != NULL){
		listOfShoots.push_back(s);
	}
}

//---------------------------------------------------------------------------------------
// this function handle wrong catch
//---------------------------------------------------------------------------------------
void TheMathGame::HandleWrongCatch(Player& pl, CreateExercise::ExerciseErrMsg ErrMsg){
	// Case its player1 wrong catch
	// check if in the if condition GameDB.GetElementByPoint(player2.getLocationPoint()) != Player::PLAYER_2_SIGN is needed
	if (IsWrongCatch(pl,ErrMsg)){
		pl.addToErrorCounter();

		// case 2 digits number delete from screen the second digit
		if (GameDB.GetElementByPoint(pl.getLocationPoint()) > ScreenData::TOW_DIGIT_VALUE){
			gotoxy(player1.getLocationPoint().getX() + 1, pl.getLocationPoint().getY());
			cout << " ";
			gotoxy(pl.getLocationPoint().getX() - 1, pl.getLocationPoint().getY());
			cout << " ";
		}
		// Delete from DB = the reason i decided that mathGame shoud delete is that i don't want
		// Player class will get the db as a reference at all
		GameDB.remove_point(pl.getLocationPoint());
	}
}

//---------------------------------------------------------------------------------------
// this function returns a boolean if its a wrong catch
//---------------------------------------------------------------------------------------
bool TheMathGame::IsWrongCatch(Player& pl, CreateExercise::ExerciseErrMsg ErrMsg) {
	/*bool tmp1 = false, tmp2 = false, tmp3 = false;

	tmp1 = GameDB.GetElementByPoint(pl.getLocationPoint()) != ScreenData::VALUE_NOT_FOUND ;
	tmp2 = (GameDB.GetElementByPoint(pl.getLocationPoint()) != Player::PLAYER_1_SIGN &&
	GameDB.GetElementByPoint(pl.getLocationPoint()) != Player::PLAYER_2_SIGN);
	tmp3 = (ErrMsg == CreateExercise::WRONG_VALUE);

	return(tmp1&&tmp2&&tmp3 );*/
	return(GameDB.GetElementByPoint(pl.getLocationPoint()) != ScreenData::VALUE_NOT_FOUND &&
			(GameDB.GetElementByPoint(pl.getLocationPoint()) != Player::PLAYER_1_SIGN &&
			GameDB.GetElementByPoint(pl.getLocationPoint()) != Player::PLAYER_2_SIGN) &&
			(ErrMsg == CreateExercise::WRONG_VALUE));
}

//---------------------------------------------------------------------------------------
// this function handle if player has max errors
//---------------------------------------------------------------------------------------
void TheMathGame::HandlePlayerUsedAllErr(Player& pl){
	if (IsPlayerUsedAllErr(pl)){
		GameDB.remove_point(pl.getLocationPoint());
		pl.setDirection(Direction::STAY); // Set player as stay
		gotoxy(pl.getLocationPoint());
		cout << " "; // Delete the player from screen
		pl.setLocationPoint(NULL, NULL); // won't be exist when checking if a crush happend
	}
}

//---------------------------------------------------------------------------------------
// this function returns a bool if its max errors
//---------------------------------------------------------------------------------------
bool TheMathGame::IsPlayerUsedAllErr(Player& pl){
	return(pl.getErrorCounter() == Player::MAX_ERROR_FOR_MATH_GAME);
}

//---------------------------------------------------------------------------------------
// this function returns a bool if shoot hitted
//---------------------------------------------------------------------------------------
bool TheMathGame::IsShootHitted(Shoot& sht, Player& pl){
	return((sht.getNextLocation() == pl.getLocationPoint()));
}

//---------------------------------------------------------------------------------------
// this function handle shoot hitted
//---------------------------------------------------------------------------------------
void TheMathGame::HandleShootHitted(Player& pl, Player::numberOfPlayer NumOfPlayer ){
	int x, y;
	Direction::value dir;
	x = (NumOfPlayer == Player::One) ? Player::PLAYER_1_X_POSITION : Player::PLAYER_2_X_POSITION;
	y = (NumOfPlayer == Player::One) ? Player::PLAYER_2_Y_POSITION : Player::PLAYER_2_Y_POSITION;
	dir = (NumOfPlayer == Player::One) ? Direction::RIGHT : Direction::LEFT;
	pl.setLocationPoint( x, y );
	pl.setDirection(dir);
}


//---------------------------------------------------------------------------------------
// this function returns a bool player crash
//---------------------------------------------------------------------------------------
bool  TheMathGame::IsPlayersCrash( Player& pl1, Player& pl2){
	return(pl1.getNextLocation() == pl2.getNextLocation());
}

//---------------------------------------------------------------------------------------
// this function handle player crash
//---------------------------------------------------------------------------------------
void TheMathGame::HandlePlayersCrash(Player& pl1, Player& pl2){
	if (pl1.getNextLocation() != pl2.getLocationPoint()){
		GameDB.remove_point(pl1.getLocationPoint());
		pl1.move();
	}
	if (pl2.getNextLocation() != pl1.getLocationPoint()){
		GameDB.remove_point(pl2.getLocationPoint());
		pl2.move();
	}

	pl1.setDirection(Direction::STAY);
	pl2.setDirection(Direction::STAY);
}