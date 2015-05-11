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
static int sub = 0;
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
// init player to first position
//---------------------------------------------------------------------------------------
void TheMathGame::initPlayerToFirstPosition(Player::numberOfPlayer numberOfPlayer){
	int x, y;
	Direction::value d;

	if (numberOfPlayer == Player::One){
		player1.setLocationPoint(Player::PLAYER_1_X_POSITION, Player::PLAYER_1_Y_POSITION);
		player1.setDirection(Direction::RIGHT);
	}
	else if (numberOfPlayer == Player::Two){
		player2.setLocationPoint(Player::PLAYER_2_X_POSITION, Player::PLAYER_2_Y_POSITION);
		player2.setDirection(Direction::LEFT);
	}
}
//---------------------------------------------------------------------------------------
// init params for level begining
//---------------------------------------------------------------------------------------
void TheMathGame::initParams(int currentLevel){
	iterationCounter = 0;
	cleanShootList();
	player1.initErrorCounter();
	player1.initShootCounter();
	initPlayerToFirstPosition(player1.getPlayerNumber());
	
	player2.initErrorCounter();
	player2.initShootCounter();
	initPlayerToFirstPosition(player2.getPlayerNumber());
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

	gotoxy(20, 0);
	cout << iterationCounter/* << "::" << sub*/;
	writeOnScreenLocation(Lines::LINE_ONE_RIGHT, "Player 1 SHOOTS: " + 
		                                         to_string(player1.getShootCounter()) + 
												 " Player 2 SHOOTS: " + 
												 to_string(player2.getShootCounter()));
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
	UpdateShootCounter();

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
	if (isPlayersCrash(player1, player2)){
		handlePlayersCrash(player1,player2);
	}
	else{
		GameDB.remove_point(player1.getLocationPoint());
		player1.move();
		GameDB.remove_point(player2.getLocationPoint());
		player2.move();
	}	
	

	CreateExercise::ExerciseErrMsg ExerMsgForPlayer1 = checkExerciseSolved(player1, currentLevel);
	CreateExercise::ExerciseErrMsg ExerMsgForPlayer2 = checkExerciseSolved(player2, currentLevel);
	
	//check if not won
	if ((ExerMsgForPlayer1 != CreateExercise::ExerciseErrMsg::SOLVED) && (ExerMsgForPlayer2 != CreateExercise::ExerciseErrMsg::SOLVED))
	{
		// Case its player wrong catch
		if (isWrongCatch(player1, ExerMsgForPlayer1))
			handleWrongCatch(player1, ExerMsgForPlayer1);
		if (isWrongCatch(player2, ExerMsgForPlayer2))
			handleWrongCatch(player2, ExerMsgForPlayer2);
	}
		

	GameDB.insert_point(player1.getLocationPoint(), Player::PLAYER_1_SIGN); 
	GameDB.insert_point(player2.getLocationPoint(), Player::PLAYER_2_SIGN);

	// case error point exceeded its range delete player from DB
	if (isPlayerUsedAllErr(player1) )
		handlePlayerUsedAllErr(player1, currentLevel);
		
	if (isPlayerUsedAllErr(player2))
		handlePlayerUsedAllErr(player2, currentLevel);

	// Do it just 1 time at 5 iterations
	if (getIterationCounter() % 5 == 0){
		// Add random number to screen
		addRandomNunberToScreen(currentLevel);
	}
}

//---------------------------------------------------------------------------------------
// this function add random point to screen
//---------------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------------
// this function handle shoot crash number
//---------------------------------------------------------------------------------------
void TheMathGame::handleShootCrashNumber(list<Shoot>::iterator it){
	int nextLocationData = GameDB.GetElementByPoint(it->getNextLocation());
	int currLocationData = GameDB.GetElementByPoint(it->getLocationPoint());

	if (nextLocationData != ScreenData::VALUE_NOT_FOUND){
		CleanScreenAtPoint(it->getNextLocation());

		if (nextLocationData > ScreenData::TOW_DIGIT_VALUE){
			CleanScreenAtPoint(it->getNextLocation().getX() + 1, it->getNextLocation().getY());
			CleanScreenAtPoint(it->getNextLocation().getX() - 1, it->getNextLocation().getY());
		}

		GameDB.remove_point(it->getNextLocation());
	}
	else{
		CleanScreenAtPoint(it->getLocationPoint());

		if (currLocationData > ScreenData::TOW_DIGIT_VALUE){
			CleanScreenAtPoint(it->getLocationPoint().getX() + 1, it->getLocationPoint().getY());
			CleanScreenAtPoint(it->getLocationPoint().getX() - 1, it->getLocationPoint().getY());
		}

		GameDB.remove_point(it->getLocationPoint());
	}
}

//---------------------------------------------------------------------------------------
// this function handle shoot crash player
//---------------------------------------------------------------------------------------
void TheMathGame::handleShootCrashPlayer(Player::numberOfPlayer numberOfPlayer, int currentLevel){
	if (numberOfPlayer == Player::One){
		GameDB.remove_point(player1.getLocationPoint());
		CleanScreenAtPoint(player1.getLocationPoint());

		if (!isPlayerUsedAllErr(player1)){
			player1.addToErrorCounter();
			initPlayerToFirstPosition(player1.getPlayerNumber());
			GameDB.insert_point(player1.getLocationPoint(), Player::PLAYER_1_SIGN);
			checkExerciseSolved(player1, currentLevel);
		}
	}
	else if(numberOfPlayer == Player::Two){
		GameDB.remove_point(player2.getLocationPoint());
		CleanScreenAtPoint(player2.getLocationPoint());

		if (!isPlayerUsedAllErr(player2)){
			player2.addToErrorCounter();
			initPlayerToFirstPosition(player2.getPlayerNumber());
			GameDB.insert_point(player2.getLocationPoint(), Player::PLAYER_2_SIGN);
			checkExerciseSolved(player2, currentLevel);
		}
	}
}
//---------------------------------------------------------------------------------------
// this function respomsible to the shoots in the game
//---------------------------------------------------------------------------------------
void TheMathGame::doSubIteration(unsigned int currentLevel){
	bool isShootTouched = false;
	sub++;
	// Move the shoots
	for (list<Shoot>::iterator it = listOfShoots.begin(); it != listOfShoots.end();){
		// Case crashed player one
		if (it->getLocationPoint() == player1.getLocationPoint()){
			handleShootCrashPlayer(player1.getPlayerNumber(), currentLevel);

			isShootTouched = true;
		}
		else if (it->getNextLocation() == player1.getLocationPoint()){
			it->move();
			handleShootCrashPlayer(player1.getPlayerNumber(), currentLevel);

			isShootTouched = true;
		}
		// Case crashed player two
		else if (it->getLocationPoint() == player2.getLocationPoint()){
			handleShootCrashPlayer(player2.getPlayerNumber(), currentLevel);

			isShootTouched = true;
		}
		else if (it->getNextLocation() == player2.getLocationPoint()){
			it->move();
			handleShootCrashPlayer(player2.getPlayerNumber(), currentLevel);

			isShootTouched = true;
		}
		// Case crashed number
		else if (GameDB.GetElementByPoint(it->getLocationPoint()) != ScreenData::VALUE_NOT_FOUND){
			handleShootCrashNumber(it);
			
			isShootTouched = true;
		}
		else if (GameDB.GetElementByPoint(it->getNextLocation()) != ScreenData::VALUE_NOT_FOUND){
			it->move();
			handleShootCrashNumber(it);

			isShootTouched = true;
		}
		// Move
		GameDB.remove_point(it->getLocationPoint());
		if (!isShootTouched){
			it->move();
			it++;
		}
		// Remove shoot
		else{
			isShootTouched = false;
			CleanScreenAtPoint(it->getLocationPoint());
			it = listOfShoots.erase(it);
		}
	}
		
}

//---------------------------------------------------------------------------------------
// this function checks exercise solved
//---------------------------------------------------------------------------------------
CreateExercise::ExerciseErrMsg TheMathGame::checkExerciseSolved(Player& player, int currentLevel){
	CreateExercise::ExerciseErrMsg ExerMsgForPlayer = getExcercise(player.getPlayerNumber()).IsProblemSolved(GameDB.GetElementByPoint(player.getLocationPoint()));

	//check if won
	if (ExerMsgForPlayer == CreateExercise::SOLVED){
		setGameWinner(player, currentLevel);
	}

	return ExerMsgForPlayer;
}
//---------------------------------------------------------------------------------------
// this function gets a direction as param and move the suit player  
//---------------------------------------------------------------------------------------
void TheMathGame::setKeyValues(Player::PLAYER_KEYS curr_input){

	switch (curr_input){
	case Player::PLAYER_1_DOWN:{
		if (!isPlayerUsedAllErr(player1)){
			player1.setDirection(Direction::DOWN);
		}

		break;
	}
	case Player::PLAYER_1_UP:{
		if (!isPlayerUsedAllErr(player1)){
			player1.setDirection(Direction::UP);
		}

		break;
	}
	case Player::PLAYER_1_LEFT:{
		if (!isPlayerUsedAllErr(player1)){
			player1.setDirection(Direction::LEFT);
		}

		break;
	}
	case Player::PLAYER_1_RIGHT:{
		if (!isPlayerUsedAllErr(player1)){
			player1.setDirection(Direction::RIGHT);
		}

		break;
	}
	case Player::PLAYER_2_DOWN:{
		if (!isPlayerUsedAllErr(player2)){
			player2.setDirection(Direction::DOWN);
		}

		break;
	}
	case Player::PLAYER_2_LEFT:{
		if (!isPlayerUsedAllErr(player2)){
			player2.setDirection(Direction::LEFT);
		}

		break;
	}
	case Player::PLAYER_2_RIGHT:{
		if (!isPlayerUsedAllErr(player2)){
			player2.setDirection(Direction::RIGHT);
		}

		break;
	}
	case Player::PLAYER_2_UP:{
		if (!isPlayerUsedAllErr(player2)){
			player2.setDirection(Direction::UP);
		}

		break;
	}
	case Player::PLAYER_1_SHOOT:{
		if (!isPlayerUsedAllErr(player1)){
			if (notDupShootInIteration() && player1.shoot()) {
				addShoot(Shoot(player1.getDirection(), player1.getNextLocation(), getIterationCounter()));
			}
		}

		break;
	}
	case Player::PLAYER_2_SHOOT:{
		if (!isPlayerUsedAllErr(player2)){
			if (notDupShootInIteration() && player2.shoot()) {
				addShoot(Shoot(player2.getDirection(), player2.getNextLocation(), getIterationCounter()));
			}
		}

		break;
	}
	default:{
		break;
	}
	}
}

//---------------------------------------------------------------------------------------
// not a dup shoot
//---------------------------------------------------------------------------------------
bool TheMathGame::notDupShootInIteration(){
	for (list<Shoot>::iterator it = listOfShoots.begin(); it != listOfShoots.end(); it++){
		if (it->getIterationShooted() == getIterationCounter()){
			return false;
		}
	}

	return true;
}

//---------------------------------------------------------------------------------------
// ctor
//---------------------------------------------------------------------------------------
TheMathGame::TheMathGame() : excersisePlayer_1(NULL), excersisePlayer_2(NULL), player1(Player::One), player2(Player::Two), iterationCounter(0)/*, listOfShoots(NULL)*/{
	// init the array of wins
	for (int i = 1; i <= TOTAL_NUMBER_OF_LEVELS; i++)
	{
		setLevelResult(NO_BODY_WON, i);
	}
}

//---------------------------------------------------------------------------------------
// dtor
//---------------------------------------------------------------------------------------
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
	listOfShoots.clear();
}

//---------------------------------------------------------------------------------------
// this function update shoot counter: every 200 iterations one more shoot
//---------------------------------------------------------------------------------------
void TheMathGame::UpdateShootCounter(){
	if (((getIterationCounter() % SHOOT_PER_ITERATION) == 0) &&
		(getIterationCounter() != 0)){
		player1.addToShootCounter();
		player2.addToShootCounter();
	}
}

//---------------------------------------------------------------------------------------
// this function add shoot to game
//---------------------------------------------------------------------------------------
void TheMathGame::addShoot(const Shoot& s){
	listOfShoots.push_back(s);
}

//---------------------------------------------------------------------------------------
// this function handle wrong catch
//---------------------------------------------------------------------------------------
void TheMathGame::handleWrongCatch(Player& pl, CreateExercise::ExerciseErrMsg ErrMsg){
	// Case its player wrong catch
	// check if in the if condition GameDB.GetElementByPoint(player2.getLocationPoint()) != Player::PLAYER_2_SIGN is needed
	if (isWrongCatch(pl,ErrMsg)){
		pl.addToErrorCounter();

		// case 2 digits number delete from screen the second digit
		if (GameDB.GetElementByPoint(pl.getLocationPoint()) > ScreenData::TOW_DIGIT_VALUE){
			CleanScreenAtPoint(pl.getLocationPoint().getX() + 1, pl.getLocationPoint().getY());
			CleanScreenAtPoint(pl.getLocationPoint().getX() - 1, pl.getLocationPoint().getY());
		}
		// Delete from DB = the reason i decided that mathGame shoud delete is that i don't want
		// Player class will get the db as a reference at all
		GameDB.remove_point(pl.getLocationPoint());
	}
}

//---------------------------------------------------------------------------------------
// this function returns a boolean if its a wrong catch
//---------------------------------------------------------------------------------------
bool TheMathGame::isWrongCatch(Player& pl, CreateExercise::ExerciseErrMsg ErrMsg) {
	return(GameDB.GetElementByPoint(pl.getLocationPoint()) != ScreenData::VALUE_NOT_FOUND &&
			(GameDB.GetElementByPoint(pl.getLocationPoint()) != Player::PLAYER_1_SIGN &&
			GameDB.GetElementByPoint(pl.getLocationPoint()) != Player::PLAYER_2_SIGN) &&
			(ErrMsg == CreateExercise::WRONG_VALUE));
}

//---------------------------------------------------------------------------------------
// this function handle if player has max errors
//---------------------------------------------------------------------------------------
void TheMathGame::handlePlayerUsedAllErr(Player& pl, int currentLevel){
	//if (isPlayerUsedAllErr(pl)){
		GameDB.remove_point(pl.getLocationPoint());
		pl.setDirection(Direction::STAY); // Set player as stay
		CleanScreenAtPoint(pl.getLocationPoint());// Delete the player from screen
		pl.setLocationPoint(NULL, NULL); // won't be exist when checking if a crush happend
		setLevelResult(TheMathGame::ERROR_TWO_PLAYERS, currentLevel);
	//}
}

//---------------------------------------------------------------------------------------
// this function returns a bool if its max errors
//---------------------------------------------------------------------------------------
bool TheMathGame::isPlayerUsedAllErr(const Player& pl){
	return(pl.getErrorCounter() >= Player::MAX_ERROR_FOR_MATH_GAME);
}

//---------------------------------------------------------------------------------------
// this function returns a bool player crash
//---------------------------------------------------------------------------------------
bool  TheMathGame::isPlayersCrash(Player& pl1, Player& pl2){
	bool oppositeDirections = (pl1.getDirection() == Direction::DOWN && pl2.getDirection() == Direction::UP) || (pl1.getDirection() == Direction::UP && pl2.getDirection() == Direction::DOWN) || (pl1.getDirection() == Direction::RIGHT && pl2.getDirection() == Direction::LEFT) || (pl1.getDirection() == Direction::LEFT && pl2.getDirection() == Direction::RIGHT);
	bool nextLocation = (pl1.getNextLocation() == pl2.getNextLocation()) || (pl1.getLocationPoint() == pl2.getNextLocation());
	bool bAll = (pl1.getNextLocation() == pl2.getNextLocation()) || (oppositeDirections && nextLocation);
	return(bAll);
}

//---------------------------------------------------------------------------------------
// this function handle player crash
//---------------------------------------------------------------------------------------
void TheMathGame::handlePlayersCrash(Player& pl1, Player& pl2){
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

//---------------------------------------------------------------------------------------
// this function handle player crash
//---------------------------------------------------------------------------------------
bool TheMathGame::hasNextLevel(unsigned int currentLevel) const {
	bool result = (currentLevel < TOTAL_NUMBER_OF_LEVELS);

	// Check if game finished so print the winner
	string sentence = "";

	if (!result){
		CleanTopOfScreen();

		if (player1.getWinCounter() > player2.getWinCounter()){
			sentence = "PLAYER 1 WON !!";
		}
		else if (player1.getWinCounter() < player2.getWinCounter()){
			sentence = "PLAYER 2 WON !!";
		}
		// tie
		else{
			sentence = "IT WAS TIE";
		}

		writeOnScreenLocation(Lines::LINE_ONE_MIDDLE, sentence);
	}

	return result;
}

//---------------------------------------------------------------------------------------
// this function set exercise
//---------------------------------------------------------------------------------------
void TheMathGame::setExercise(Player::numberOfPlayer playerNumber, unsigned int currentLevel){
	if (playerNumber == Player::One){
		excersisePlayer_1 = CreateExercise(currentLevel);
	}
	else{
		excersisePlayer_2 = CreateExercise(currentLevel);
	}
}