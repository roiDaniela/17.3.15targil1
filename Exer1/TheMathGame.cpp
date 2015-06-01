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
	writeOnScreenLocation(LINE_ONE_LEFT, "Level Number: " + to_string(currentLevel));
	writeOnScreenLocation(LINE_TWO_LEFT, "Exercise Player 1: " + getExcercise(Player::One).getHiddenExercise());
	writeOnScreenLocation(LINE_TWO_RIGHT, "Exercise Player 2: " + getExcercise(Player::Two).getHiddenExercise());
	
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
		writeOnScreenLocation(LINE_ONE_MIDDLE, "Its over than 1500 turns clock!!!!!");
		writeOnScreenLocation(LINE_THREE_LEFT, "Points Player 1: " + to_string(player1.getWinCounter()));
		writeOnScreenLocation(LINE_THREE_RIGHT, "Points Player 2: " + to_string(player2.getWinCounter()));
		Sleep(1500);
		return true;
	}

	return false;
}

//---------------------------------------------------------------------------------------
// init player to first position
//---------------------------------------------------------------------------------------
void TheMathGame::initPlayerToFirstPosition(Player::numberOfPlayer numberOfPlayer){
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
	setLevelResult(TheMathGame::NO_BODY_WON);
	iterationCounter = 0;
	cleanShootList();
	player1.initErrorCounter();
	player1.initShootCounter();
	initPlayerToFirstPosition(player1.getPlayerNumber());
	player1.setPrevDirection(Direction::RIGHT);

	player2.initErrorCounter();
	player2.initShootCounter();
	initPlayerToFirstPosition(player2.getPlayerNumber());
	player2.setPrevDirection(Direction::LEFT);
	if (currentLevel == 1){
		player1.initWinCounter();
		player2.initWinCounter();
	}

	cleanFlyersCreatureList();
	
	rowFlyer1.setLocationPoint(Point(30, 23));
	rowFlyer1.setDirection(Direction::RIGHT);
	rowFlyer2.setLocationPoint(Point(50, 15));
	rowFlyer2.setDirection(Direction::LEFT);
	colFlyer1.setLocationPoint(Point(45, 23));
	colFlyer1.setDirection(Direction::UP);
	colFlyer2.setLocationPoint(Point(55, 15));
	colFlyer2.setDirection(Direction::DOWN);
	
	numEater1.setLocationPoint(Point(10, 19));
	numEater1.setDirection(Direction::STAY);
	numEater1.setIsAlive(true);
	numEater2.setLocationPoint(Point(70, 19));
	numEater2.setDirection(Direction::STAY);
	numEater2.setIsAlive(true);

	addFlyer(&rowFlyer1);
	addFlyer(&rowFlyer2);
	addFlyer(&colFlyer1);
	addFlyer(&colFlyer2);
	//addFlyer(&numEater1);
	//addFlyer(&numEater2);

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
	writeOnScreenLocation(LINE_ONE_LEFT, "Level Number: " + to_string(currentLevel));
	writeOnScreenLocation(LINE_TWO_LEFT, "Exercise Player 1: " + getExcercise(Player::One).getHiddenExercise());
	writeOnScreenLocation(LINE_TWO_RIGHT, "Exercise Player 2: " + getExcercise(Player::Two).getHiddenExercise());

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

	writeOnScreenLocation(LINE_ONE_RIGHT, "Iteration: " + to_string(getIterationCounter()));
	
	string sentence = "P1 Errors: ";
	playerErrors = (TOTAL_NUMBER_OF_ERRORS - player1.getErrorCounter());
	for (int i = 0; i < playerErrors; i++)
	{
		sentence += "*";
	}
	sentence += " Shoots:" + to_string(player1.getShootCounter());
	sentence += "  Points:" + to_string(player1.getWinCounter());

	writeOnScreenLocation(LINE_THREE_LEFT, sentence);

	sentence = "P2 Errors: ";
	playerErrors = (TOTAL_NUMBER_OF_ERRORS - player2.getErrorCounter());
	for (int i = 0; i < playerErrors; i++)
	{
		sentence += "*";
	}
	sentence += " Shoots:" + to_string(player2.getShootCounter());
	sentence += "  Points:" + to_string(player2.getWinCounter());

	writeOnScreenLocation(LINE_THREE_RIGHT, sentence);
}

//---------------------------------------------------------------------------------------
// this method responsible on the itaertion in curr level, one of two major 
// methods of the class 
//---------------------------------------------------------------------------------------
void TheMathGame::doIteration(const list<char>& keyHits, unsigned int currentLevel){
	bool isPlayer1ShootedThisIteration = false;
	bool isPlayer2ShootedThisIteration = false;
	
	//Point* ptDebugNearestPoint = GameDB.GetNearestPoint(numEater1.getLocationPoint());

	prepareStatusSentenceOnScreen();
	
	// Check its not over than 1500 turns and update the players itaeration
	updateIterationCounter();
	updateShootCounter();

	// pass over the keyHits in order to collect the players input
	for (list<char>::const_iterator itr = keyHits.begin();
		itr != keyHits.end();
		++itr)
	{
		Player::PLAYER_KEYS curr_input = static_cast<Player::PLAYER_KEYS>(*itr);

		setKeyValues(curr_input, isPlayer1ShootedThisIteration, isPlayer2ShootedThisIteration);
	}

	// Check the next location of players: in case they will meet set them as 'stay' otherwise set their 
	// direction
	if (isPlayersCrash(player1, player2)){
		handlePlayersCrash(player1,player2);
	}
	else{
		cleanTwoDigitsFromScreen(player1.getLocationPoint());
		GameDB.remove_point(player1.getLocationPoint());
		player1.move(getIterationCounter());
		
		cleanTwoDigitsFromScreen(player2.getLocationPoint());
		GameDB.remove_point(player2.getLocationPoint());
		player2.move(getIterationCounter());
	}	

	CreateExercise::ExerciseErrMsg ExerMsgForPlayer1 = checkExerciseSolved(player1, currentLevel);
	CreateExercise::ExerciseErrMsg ExerMsgForPlayer2 = checkExerciseSolved(player2, currentLevel);
	
	//check if not won
	if ((ExerMsgForPlayer1 != CreateExercise::SOLVED) && (ExerMsgForPlayer2 != CreateExercise::SOLVED))
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
		
		// Get the new target Point
		setNewTargetPointForNumEater();
	}

	/*numEater1.setPlayer1LocPoint(player1.getNextLocation());
	numEater1.setPlayer1LocPoint(player2.getNextLocation());
	numEater2.setPlayer1LocPoint(player1.getNextLocation());
	numEater2.setPlayer1LocPoint(player2.getNextLocation());*/
}

//---------------------------------------------------------------------------------------
// this function set new target point to num eater
//---------------------------------------------------------------------------------------
void TheMathGame::setNewTargetPointForNumEater(){
	numEater1.setTargetLocPoint(GameDB.GetNearestPoint(numEater1.getLocationPoint()));
	numEater2.setTargetLocPoint(GameDB.GetNearestPoint(numEater2.getLocationPoint()));
}

//---------------------------------------------------------------------------------------
// this function add random point to screen
//---------------------------------------------------------------------------------------
void TheMathGame::addRandomNunberToScreen(unsigned int currentLevel){
	unsigned int value;
	
	// Case its 1-20 level then value is between level number to 1, 
	// Case ots 21-40 level then value is between 1-20
	if (currentLevel <= FIRST_SERIES_OF_LEVELS){
		value = RandomOutput::CreateRandomValue(RANDOM_NUMBERS_DIFF + currentLevel);
	}
	else{
		value = RandomOutput::CreateRandomValue(RANDOM_NUMBERS_DIFF + FIRST_SERIES_OF_LEVELS);
	}
	
	int numOfDigits = (value > ScreenData::TWO_DIGIT_VALUE) ? 2 : 1;
	Point* ptTmp = RandomOutput::CreateRandomPoint(GameDB, numOfDigits);
	if (ptTmp != NULL){
		if (GameDB.insert_point(*ptTmp, value)){
			gotoxy(*ptTmp);
			cout << value;
		}
	}

	delete ptTmp;
}

//---------------------------------------------------------------------------------------
// this function handle shoot crash number
//---------------------------------------------------------------------------------------
void TheMathGame::handleCreatureCrashNumber(const Point& p){
	CleanScreenAtPoint(p);

	cleanTwoDigitsFromScreen(p);

	GameDB.remove_point(p);

	setNewTargetPointForNumEater();
}

//---------------------------------------------------------------------------------------
// this function handle shoot crash player
//---------------------------------------------------------------------------------------
void TheMathGame::handleCreatureCrashPlayer(Player::numberOfPlayer numberOfPlayer, int currentLevel){
	if (numberOfPlayer == Player::One){
		CleanScreenAtPoint(player1.getLocationPoint());
		
		cleanTwoDigitsFromScreen(player1.getLocationPoint()); // check if needed

		GameDB.remove_point(player1.getLocationPoint());

		if (!isPlayerUsedAllErr(player1)){
			player1.addToErrorCounter();
			initPlayerToFirstPosition(player1.getPlayerNumber());
			GameDB.insert_point(player1.getLocationPoint(), Player::PLAYER_1_SIGN);
			checkExerciseSolved(player1, currentLevel);
		}
	}
	else if(numberOfPlayer == Player::Two){
		CleanScreenAtPoint(player2.getLocationPoint());
		
		cleanTwoDigitsFromScreen(player2.getLocationPoint()); // check if neede
		
		GameDB.remove_point(player2.getLocationPoint());

		if (!isPlayerUsedAllErr(player2)){
			player2.addToErrorCounter();
			initPlayerToFirstPosition(player2.getPlayerNumber());
			GameDB.insert_point(player2.getLocationPoint(), Player::PLAYER_2_SIGN);
			checkExerciseSolved(player2, currentLevel);
		}
	}
}

//---------------------------------------------------------------------------------------
// this function handle case shoot crash a flyer
//---------------------------------------------------------------------------------------
void TheMathGame::handleShootCrashCreature(){
	bool bIsCrashedNumEater = false;
	for (list<Shoot>::iterator itShoot = listOfShoots.begin(); itShoot != listOfShoots.end(); ){
		bIsCrashedNumEater = numEater1.getLocationPoint() == itShoot->getLocationPoint() ||
							 numEater1.getNextLocation() == itShoot->getLocationPoint() ||
						     numEater2.getLocationPoint() == itShoot->getLocationPoint() ||
						     numEater2.getNextLocation() == itShoot->getLocationPoint();
		
		for (list<Creature*>::iterator itFlyer = listOfFlyers.begin(); itFlyer != listOfFlyers.end() && itShoot != listOfShoots.end(); itFlyer++){
			// remove shoot crash flyer
			if (bIsCrashedNumEater || 
				((*itFlyer)->getLocationPoint() == itShoot->getLocationPoint() ||
				(*itFlyer)->getNextLocation() == itShoot->getLocationPoint())){
				itShoot = listOfShoots.erase(itShoot);
			}
			else{
				itShoot++;
			}
		}
		bIsCrashedNumEater = false;
	}
}

//---------------------------------------------------------------------------------------
// this function handle creature crashes
//---------------------------------------------------------------------------------------
bool TheMathGame::handleCreatureCrashes(Creature& it, int currentLevel){
	bool isTouched = false;

	// Case crashed player one
	if (it.getLocationPoint() == player1.getLocationPoint()){
		handleCreatureCrashPlayer(player1.getPlayerNumber(), currentLevel);

		isTouched = true;
	}
	else if (it.getNextLocation() == player1.getLocationPoint()){
		it.move(getIterationCounter());
		handleCreatureCrashPlayer(player1.getPlayerNumber(), currentLevel);

		isTouched = true;
	}
	// Case crashed player two
	else if (it.getLocationPoint() == player2.getLocationPoint()){
		handleCreatureCrashPlayer(player2.getPlayerNumber(), currentLevel);

		isTouched = true;
	}
	else if (it.getNextLocation() == player2.getLocationPoint()){
		it.move(getIterationCounter());
		handleCreatureCrashPlayer(player2.getPlayerNumber(), currentLevel);

		isTouched = true;
	}
	// Case crashed number
	else if (GameDB.GetElementByPoint(it.getLocationPoint()) != ScreenData::VALUE_NOT_FOUND){
		handleCreatureCrashNumber(it.getLocationPoint());

		isTouched = true;
	}
	else if (GameDB.GetElementByPoint(it.getNextLocation()) != ScreenData::VALUE_NOT_FOUND){
		it.move(getIterationCounter());
		handleCreatureCrashNumber(it.getLocationPoint());

		isTouched = true;
	}

	return isTouched;
}

bool TheMathGame::handleNumEaterCrashPlayer(){
	bool isDeletedNumEater = false;

	if (numEater1.getIsAlive() && 
		(numEater1.getLocationPoint() == player1.getLocationPoint() ||
		numEater1.getLocationPoint() == player2.getLocationPoint())){

		numEater1.setIsAlive(false);

		CleanScreenAtPoint(numEater1.getLocationPoint());

		isDeletedNumEater = true;
	}
	else if (numEater2.getIsAlive() && 
		     (numEater2.getLocationPoint() == player1.getLocationPoint() ||
		     numEater2.getLocationPoint() == player2.getLocationPoint())){

		numEater2.setIsAlive(false);

		CleanScreenAtPoint(numEater2.getLocationPoint());

		isDeletedNumEater = true;
	}
	else if (numEater1.getIsAlive() &&
		    (numEater1.getNextLocation() == player1.getLocationPoint() ||
			numEater1.getNextLocation() == player2.getLocationPoint())){
		numEater1.move(getIterationCounter());

		numEater1.setIsAlive(false);

		CleanScreenAtPoint(numEater1.getLocationPoint());
		
		isDeletedNumEater = true;
	}
	else if (numEater2.getIsAlive() && 
			(numEater2.getNextLocation() == player1.getLocationPoint() ||
			numEater2.getNextLocation() == player2.getLocationPoint())){
		numEater2.move(getIterationCounter());

		numEater2.setIsAlive(false);

		CleanScreenAtPoint(numEater2.getLocationPoint());

		isDeletedNumEater = true;
	}

	return isDeletedNumEater;
}
//---------------------------------------------------------------------------------------
// this function handle Num eater crash
//---------------------------------------------------------------------------------------
bool TheMathGame::handleNumEaterCrashes(int currentLevel){
	bool isDeletedNumEater = false;
	
	// Case Crashed numEaters
	if (!isDeletedNumEater){
		isDeletedNumEater = handleNumEaterCrashNumEater();
	}

	// Case crashed players
	if (!isDeletedNumEater){
		isDeletedNumEater = handleNumEaterCrashPlayer();
	}

	// Case crashed flyers

	// Case crashed number
	if (!isDeletedNumEater){
		isDeletedNumEater = handleNumEaterCrashNumber();
	}
	
	return isDeletedNumEater;
}

//---------------------------------------------------------------------------------------
// this function respomsible to the shoots in the game
//---------------------------------------------------------------------------------------
bool TheMathGame::handleNumEaterCrashNumber(){
	bool isDeletedNumEater = false;

	if (numEater1.getIsAlive() && 
		(GameDB.GetElementByPoint(numEater1.getLocationPoint()) != ScreenData::VALUE_NOT_FOUND)){
		handleCreatureCrashNumber(numEater1.getLocationPoint());

		// may needed to enter another point to search
		numEater1.setTargetLocPoint(GameDB.GetNearestPoint(numEater1.getLocationPoint()));

		//isDeletedNumEater = true;
	}
	else if (numEater2.getIsAlive() &&
		    (GameDB.GetElementByPoint(numEater2.getLocationPoint()) != ScreenData::VALUE_NOT_FOUND)){
		handleCreatureCrashNumber(numEater2.getLocationPoint());

		// may needed to enter another point to search
		numEater2.setTargetLocPoint(GameDB.GetNearestPoint(numEater2.getLocationPoint()));

		//isDeletedNumEater = true;
	}
	else if (numEater1.getIsAlive() && 
			(GameDB.GetElementByPoint(numEater1.getNextLocation()) != ScreenData::VALUE_NOT_FOUND)){
		numEater1.move(getIterationCounter());
		handleCreatureCrashNumber(numEater1.getLocationPoint());

		// may needed to enter another point to search
		numEater1.setTargetLocPoint(GameDB.GetNearestPoint(numEater1.getLocationPoint()));

		//isDeletedNumEater = true;
	}
	else if (numEater2.getIsAlive() &&
		(GameDB.GetElementByPoint(numEater2.getNextLocation()) != ScreenData::VALUE_NOT_FOUND)){
		numEater2.move(getIterationCounter());
		handleCreatureCrashNumber(numEater2.getLocationPoint());

		// may needed to enter another point to search
		numEater2.setTargetLocPoint(GameDB.GetNearestPoint(numEater2.getLocationPoint()));

		//isDeletedNumEater = true;
	}

	return isDeletedNumEater;
}

//---------------------------------------------------------------------------------------
// this function respomsible to the shoots in the game
//---------------------------------------------------------------------------------------
void TheMathGame::doSubIteration(unsigned int currentLevel){
	bool isTouched = false;

	// case shoot crashed flyer/num eater 
	handleShootCrashCreature();

	// Move the shoots
	for (list<Shoot>::iterator it = listOfShoots.begin(); it != listOfShoots.end();){
		isTouched = handleCreatureCrashes(*it, currentLevel);
		
		// Move if not crashed
		if (!isTouched){
			it->move(getIterationCounter());
			it++;
		}
		// Remove shoot
		else{
			isTouched = false;
			it = listOfShoots.erase(it);
		}
	}
	
	// Move Flyers (rowFlyers && colFlyers)
	for (list<Creature*>::iterator it = listOfFlyers.begin(); it != listOfFlyers.end();){
		// Its a flyer
		isTouched = handleCreatureCrashes(**it, currentLevel);

		if (!isTouched){
			(*it)->move(getIterationCounter());
		}
		it++;
	}

	// Move numEaters
	calcNumEatersDirection();

	isTouched = handleNumEaterCrashes(currentLevel);

	if (!isTouched){
		if (numEater1.getIsAlive()){
			numEater1.move(getIterationCounter());
		}
		
		if (numEater2.getIsAlive()){
			numEater2.move(getIterationCounter());
		}
	}
}

//---------------------------------------------------------------------------------------
// this function calc num eater direction
//---------------------------------------------------------------------------------------
void TheMathGame::calcNumEatersDirection(){
	if (numEater1.getIsAlive()){
		numEater1.calcNumEaterDirection(player1, player2);
	}
	
	if (numEater2.getIsAlive()){
		numEater2.calcNumEaterDirection(player1, player2);
	}

	// Avoid numeaters crashing
	if ((numEater1.getIsAlive() && numEater2.getIsAlive()) &&
		(numEater1.getLocationPoint() == numEater2.getNextLocation() ||
		numEater1.getNextLocation() == numEater2.getNextLocation() ||
		numEater1.getLocationPoint() == numEater2.getLocationPoint() ||
		numEater1.getNextLocation() == numEater2.getLocationPoint())){
		if ((numEater2.getDirection() == Direction::UP && numEater1.getDirection() == Direction::DOWN) ||
			(numEater2.getDirection() == Direction::DOWN && numEater1.getDirection() == Direction::UP)){
			numEater1.setDirection(Direction::LEFT);
			numEater2.setDirection(Direction::RIGHT);
		}
		else if ((numEater2.getDirection() == Direction::RIGHT && numEater1.getDirection() == Direction::LEFT) ||
			(numEater2.getDirection() == Direction::LEFT && numEater1.getDirection() == Direction::RIGHT)){
			numEater1.setDirection(Direction::UP);
			numEater2.setDirection(Direction::DOWN);
		}
		else{
			numEater2.setDirection(Direction::getOppositeDirection(numEater2.getDirection()));
		}
		//setDirection(Direction::getOrthogonalDirection(getDirection()));
	}
}

//---------------------------------------------------------------------------------------
// this function handle numEater crash
//---------------------------------------------------------------------------------------
bool TheMathGame::handleNumEaterCrashNumEater(){	
	bool isDeletedNumEater = false;
	
	if (numEater1.getIsAlive() && numEater2.getIsAlive()){
		if (numEater1.getLocationPoint() == numEater2.getLocationPoint()){
			numEater1.setIsAlive(false);
			numEater2.setIsAlive(false);

			CleanScreenAtPoint(numEater1.getLocationPoint());

			isDeletedNumEater = true;
		}
		else if (numEater1.getLocationPoint() == numEater2.getNextLocation()){
			numEater2.move(getIterationCounter());

			numEater1.setIsAlive(false);
			numEater2.setIsAlive(false);

			CleanScreenAtPoint(numEater1.getLocationPoint());

			isDeletedNumEater = true;
		}
		else if (numEater2.getLocationPoint() == numEater1.getNextLocation()){
			numEater1.move(getIterationCounter());

			numEater1.setIsAlive(false);
			numEater2.setIsAlive(false);

			CleanScreenAtPoint(numEater1.getLocationPoint());

			isDeletedNumEater = true;
		}
		//else if (numEater1.getNextLocation() == numEater2.getNextLocation()){
		//	numEater1.move(getIterationCounter());
		//	numEater2.move(getIterationCounter());

		//	numEater1.setIsAlive(false);
		//	numEater2.setIsAlive(false);

		//	CleanScreenAtPoint(numEater1.getLocationPoint());

		//	isDeletedNumEater = true;
		//}
	}

	return isDeletedNumEater;
}
//---------------------------------------------------------------------------------------
// this function checks exercise solved
//---------------------------------------------------------------------------------------
CreateExercise::ExerciseErrMsg TheMathGame::checkExerciseSolved(Player& player, int currentLevel){
	CreateExercise::ExerciseErrMsg ExerMsgForPlayer = getExcercise(player.getPlayerNumber()).IsProblemSolved(GameDB.GetElementByPoint(player.getLocationPoint()));

	//check if won
	if (ExerMsgForPlayer == CreateExercise::SOLVED){
		setGameWinner(player);
		setNewTargetPointForNumEater();
	}

	return ExerMsgForPlayer;
}

//---------------------------------------------------------------------------------------
// this function sets the prev direction
//---------------------------------------------------------------------------------------
void TheMathGame::setThePrevDirection(Player::PLAYER_KEYS curr_input){
	if ((curr_input == Player::PLAYER_1_DOWN ||
		curr_input == Player::PLAYER_1_LEFT ||
		curr_input == Player::PLAYER_1_RIGHT ||
		curr_input == Player::PLAYER_1_UP) &&
		(player1.getDirection() != Direction::STAY)){
		player1.setPrevDirection(player1.getDirection());
	}
	else if ((curr_input == Player::PLAYER_2_DOWN ||
		curr_input == Player::PLAYER_2_LEFT ||
		curr_input == Player::PLAYER_2_RIGHT ||
		curr_input == Player::PLAYER_2_UP) &&
		(player2.getDirection() != Direction::STAY))
	{
		player2.setPrevDirection(player2.getDirection());
	}
}
//---------------------------------------------------------------------------------------
// this function gets a direction as param and move the suit player  
//---------------------------------------------------------------------------------------
void TheMathGame::setKeyValues(Player::PLAYER_KEYS curr_input, 
	                           bool& isPlayer1ShootedThisIteration, 
	                           bool& isPlayer2ShootedThisIteration){
	
	setThePrevDirection(curr_input);
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
			if (!isPlayer1ShootedThisIteration && getNonStayDirection(player1) != Direction::STAY && player1.shoot()) {
				addShoot(Shoot(getNonStayDirection(player1), player1.getNextLocation(), getIterationCounter()));
				isPlayer1ShootedThisIteration = true;
			}
		}
		
		break;
	}
	case Player::PLAYER_2_SHOOT:{
		if (!isPlayerUsedAllErr(player2)){
			if (!isPlayer2ShootedThisIteration && getNonStayDirection(player2) != Direction::STAY && player2.shoot()) {
				addShoot(Shoot(getNonStayDirection(player2), player2.getNextLocation(), getIterationCounter()));
				isPlayer2ShootedThisIteration = true;
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
// get not stay direction using prev direction
//---------------------------------------------------------------------------------------
Direction::value TheMathGame::getNonStayDirection(const Player& p) const{
	if (p.getDirection() != Direction::STAY){
		return p.getDirection();
	}
	else{
		return p.getPrevDirection();
	}
}

//---------------------------------------------------------------------------------------
// ctor
//---------------------------------------------------------------------------------------
TheMathGame::TheMathGame() : excersisePlayer_1(NULL), 
                             excersisePlayer_2(NULL),  
							 iterationCounter(0),
							 player1(Player::One, iterationCounter),
							 player2(Player::Two, iterationCounter),
							 resultOfCurrLevel(NO_BODY_WON),
							 rowFlyer1(Point(23,30), Direction::RIGHT),
							 rowFlyer2(Point(50,15), Direction::LEFT),
							 colFlyer1(Point(45,23), Direction::UP),
							 colFlyer2(Point(55,15), Direction::DOWN),
							 numEater1(Point(10, 19), Direction::STAY),
							 numEater2(Point(70, 19), Direction::STAY){

}

//---------------------------------------------------------------------------------------
// this function sets the winner in the game
//---------------------------------------------------------------------------------------
void TheMathGame::setGameWinner(Player& player){
	player.addToWinCounter();
	if (player.getPlayerNumber() == Player::One){
		setLevelResult(PLAYER_ONE_WON);
	}
	else if (player.getPlayerNumber() == Player::Two){
		setLevelResult(PLAYER_TWO_WON);
	}
}

//---------------------------------------------------------------------------------------
// this function cleans the shoot list
//---------------------------------------------------------------------------------------
void TheMathGame::cleanShootList(){
	listOfShoots.clear();
}

//---------------------------------------------------------------------------------------
// this function cleans the creature list
//---------------------------------------------------------------------------------------
void TheMathGame::cleanFlyersCreatureList(){
	listOfFlyers.clear();
}

//---------------------------------------------------------------------------------------
// this function update shoot counter: every 200 iterations one more shoot
//---------------------------------------------------------------------------------------
void TheMathGame::updateShootCounter(){
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
// this function add creature to game
//---------------------------------------------------------------------------------------
void TheMathGame::addFlyer(Creature* c){
	listOfFlyers.push_back(c);
}

//---------------------------------------------------------------------------------------
// this function removes creature from the game
//---------------------------------------------------------------------------------------
void TheMathGame::RemoveCreature(Creature* c){
	//listOfFlyers.remove(c);
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
		cleanTwoDigitsFromScreen(pl.getLocationPoint());

		// Delete from DB = the reason i decided that mathGame shoud delete is that i don't want
		// Player class will get the db as a reference at all
		GameDB.remove_point(pl.getLocationPoint());
		setNewTargetPointForNumEater();
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
	int n = GameDB.GetElementByPoint(pl.getLocationPoint());
	
	cleanTwoDigitsFromScreen(pl.getLocationPoint()); // check if needed

	CleanScreenAtPoint(pl.getLocationPoint());// Delete the player from screen
	GameDB.remove_point(pl.getLocationPoint());
	setNewTargetPointForNumEater();
	pl.setDirection(Direction::STAY); // Set player as stay
	pl.setLocationPoint(NULL, NULL); // won't be exist when checking if a crush happend
	
	// End curr level if 2 players have max errors
	if (isPlayerUsedAllErr(player1) && isPlayerUsedAllErr(player2)){
		setLevelResult(ERROR_TWO_PLAYERS);
	}
}

//---------------------------------------------------------------------------------------
// this function returns a bool if its max errors
//---------------------------------------------------------------------------------------
bool TheMathGame::isPlayerUsedAllErr(const Player& pl){
	return(pl.getErrorCounter() >= TOTAL_NUMBER_OF_ERRORS);
}

//---------------------------------------------------------------------------------------
// this function returns a bool player crash
//---------------------------------------------------------------------------------------
bool  TheMathGame::isPlayersCrash(Player& pl1, Player& pl2){
	bool oppositeDirections = (pl1.getDirection() == Direction::DOWN && pl2.getDirection() == Direction::UP) || (pl1.getDirection() == Direction::UP && pl2.getDirection() == Direction::DOWN) || (pl1.getDirection() == Direction::RIGHT && pl2.getDirection() == Direction::LEFT) || (pl1.getDirection() == Direction::LEFT && pl2.getDirection() == Direction::RIGHT);
	bool nextLocation = (pl1.getNextLocation() == pl2.getNextLocation()) || (pl1.getLocationPoint() == pl2.getNextLocation()) || (pl1.getNextLocation() == pl1.getLocationPoint());
	bool bAll = (pl1.getNextLocation() == pl2.getNextLocation()) || (oppositeDirections && nextLocation);
	return(bAll);
}

//---------------------------------------------------------------------------------------
// this function delets two digits 2 screen
//---------------------------------------------------------------------------------------
bool TheMathGame::cleanTwoDigitsFromScreen(Point pt){
	int n = GameDB.GetElementByPoint(pt);
	if (n > ScreenData::TWO_DIGIT_VALUE && n != ScreenData::PLAYER2_SIGN && n != ScreenData::PLAYER1_SIGN){
		if (pt.getX() + 1 != LENGH_OF_LINE){
			CleanScreenAtPoint(pt.getX() + 1, pt.getY());
		}

		if (pt.getX() - 1 != -1){
			CleanScreenAtPoint(pt.getX() - 1, pt.getY());
		}

		return true;
	}

	return false;
}

//---------------------------------------------------------------------------------------
// this function handle player crash
//---------------------------------------------------------------------------------------
void TheMathGame::handlePlayersCrash(Player& pl1, Player& pl2){
	if (pl1.getNextLocation() != pl2.getLocationPoint()){
		cleanTwoDigitsFromScreen(pl1.getLocationPoint());
		GameDB.remove_point(pl1.getLocationPoint());
		pl1.move(getIterationCounter());
	}
	if (pl2.getNextLocation() != pl1.getLocationPoint()){
		cleanTwoDigitsFromScreen(pl2.getLocationPoint());
		GameDB.remove_point(pl2.getLocationPoint());
		pl2.move(getIterationCounter());
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

		writeOnScreenLocation(LINE_ONE_MIDDLE, sentence);
		Sleep(1500);
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