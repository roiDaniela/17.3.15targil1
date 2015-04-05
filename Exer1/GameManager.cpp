//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// GameManager.cpp
// ---------------
// GameManager is the top level manager, the game starts from here.
// This class manages the game iterations, menus etc., but WITHOUT knowing anything about the actual game itself.
//
// Author: Amir Kirsh
// First version: 2014-12-09
// 
// This code is part of "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// In the file itself, add above each change/addition a remark saying: "NEW CODE EX1, author=<name>, date=<YYYY-MM-DD>"
// and close it at the end with a remark saying "END of NEW CODE EX1" 
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <list>
#include "GameManager.h"
#include "ISpecificGame.h"
#include "io_utils.h"
#include "TheMathGame.h"

using namespace std;

// My adding 18.3.15: This function get a string,
// take the cursor to the top and printing the string got
//void GameManager::writeOnTopOfScreen(string sentence)
//{
//	// Go to the top of the screen
//	gotoxy(0, 0);
//
//	// Clean the 2 first lines
//	for (int j = 0; j < AMOUNT_OF_INSTRUCTIONS_LINE; j++)
//	{
//		for (int i = 0; i < LENGH_OF_LINE; i++)
//		{
//			cout << "";
//		}
//	}
//	
//	cout << sentence;
//}

char GameManager::mainMenu()const
{
	// TODO: you may want to improve the menu appearance.
	// Roi's adding
	// First and second rows will be for instructions
	gotoxy(0, 3);

	cout << "1. instructions" << endl;
	cout << "2. play game" << endl;
	cout << "3. start from a specific level" << endl;
	cout << "9. exit" << endl;
	char selection = 0;
	do {
		selection = _getch();
	} while(!GameManager::MainMenuOptions::isValidOption(selection));
	return selection;
}

void GameManager::run()
{
	bool userWantsToPlay = true;
	// we run as long as the user wants
	while(userWantsToPlay) {
		char menuSelection = mainMenu();
		// TODO: handle here all the different menu options
		switch(menuSelection)
		{
			case GameManager::MainMenuOptions::PLAY_GAME:
			{
				init();
				userWantsToPlay = playGame();
				break;
			}
			// NEW CODE EX1, author=<Roi>, date=<2015-03-17>
			case GameManager::MainMenuOptions::PRESENT_INSTRUCTIONS:
			{
				string sentence = "This should be the instructions";
				writeOnScreenLocation(Lines::LINE_ONE_RIGHT, sentence);
				break;
			}
			// END of NEW CODE EX1
			// NEW CODE EX1, author=<Roi>, date=<2015-03-17>
			case GameManager::MainMenuOptions::PLAY_FROM_SELECTED_SCREEN:
			{
				int numberLevelChosen;
				string sentence = "Please enter a screen level between 1 - 20: ";
				writeOnScreenLocation(Lines::LINE_ONE_LEFT, sentence);
				gotoxy(sentence.length() + 1, 0); // GO TO end of the sentence in line 1
				cin >> numberLevelChosen;

				while (numberLevelChosen > 20 || numberLevelChosen < 1){
					writeOnScreenLocation(Lines::LINE_TWO_LEFT, "ilegal number of level: Please type a legal number");
					gotoxy(sentence.length() + 1, 0); // GO TO end of the sentence in line 1
					cin >> numberLevelChosen;
				}

				currentLevel = numberLevelChosen - 1; // start from selected level
				userWantsToPlay = playGame();

				break;
			}
			// END of NEW CODE EX1
			case GameManager::MainMenuOptions::EXIT_APPLICATION:
			{
				userWantsToPlay = false;
				break;
			}
			default: // normally we shouldn't get to here...
			{
				userWantsToPlay = false;
			}
		};
	}
}

bool GameManager::playGame()
{
	// we assume that we have multiple levels so there is a need to loop through levels
	// till all levels were played or till user quits - if user quits we do not continue to next level
	//-------------------------------------------------------------
	// this is the game LEVELS loop
	//-------------------------------------------------------------
	char action = GameManager::LevelOptions::NEXT_LEVEL;
	while(actualGame.hasNextLevel(currentLevel) && action == GameManager::LevelOptions::NEXT_LEVEL) {
		action = playNextLevel();
	}
	//-------------------------------------------------------------
	// END of game LEVELS loop
	//-------------------------------------------------------------
	
	// return true if the user wants to keep playing
	return (action != GameManager::LevelOptions::EXIT_APPLICATION);
}

// return action to take in case of ESC
char GameManager::playNextLevel()
{
	++currentLevel;
	actualGame.startLevel(currentLevel);
	//------------------------------------------------------------------------------
	// here we control the ESC menu
	//------------------------------------------------------------------------------
	bool keepRunning = true;
	char action = 0;
	while(keepRunning)
	{
		//=============================================================================================
		// this is the actual call to play game iterations
		action = doLevelIterations();
		//=============================================================================================
		
		// check action based on game ended (action==BACK_TO_MAIN_MENU) or input from user on ESC menu
		switch(action) {
		case GameManager::LevelOptions::CONTINUE: // clean the screen and add all from data base
			// keepRunning is true, so we only need to set thing right and then - keepRunning!
			//--------------------------------------------------------------------------------
			clear_screen();
			actualGame.resumeGame(currentLevel);
			break;
		case GameManager::LevelOptions::REPLAY_LEVEL:
			// keepRunning is true, so we only need to set thing right and then - keepRunning!
			//--------------------------------------------------------------------------------
			actualGame.startLevel(currentLevel);
			break;
		case GameManager::LevelOptions::BACK_TO_MAIN_MENU:
			clear_screen();
			run();
			keepRunning = false;
			action = GameManager::LevelOptions::EXIT_APPLICATION;
			break;
		case GameManager::LevelOptions::EXIT_APPLICATION:
			// get out from the loop
			clear_screen();
			keepRunning = false;
			break;
		case GameManager::LevelOptions::NEXT_LEVEL:
			// get out from the loop so we get to the next level
			keepRunning = false;
			break;
		}
		//---------------------------------------
		// END of sub menu action switch
		//---------------------------------------
	}
	//------------------------------------------
	// END of Level keepRunning loop (sub menu)
	//------------------------------------------

	// the actions that may get out from this method are: BACK_TO_MAIN_MENU and EXIT_APPLICATION
	return action;
}

// return action to take in case of ESC
char GameManager::doLevelIterations()
{
	char action;
	bool escapePressed = false;
	//---------------------------------------
	// this is the game iterations loop
	//---------------------------------------
	while(!actualGame.isLevelDone() && !escapePressed) {
		escapePressed = !doIteration();
	}
	//-----------------------------------------------------
	// END of game iterations loop or exit on ESC
	//-----------------------------------------------------

	// check why we are here
	if(actualGame.isLevelDone()) {
		clear_screen();
		CleanTopOfScreen();
		string sentence = "";
		//if (Player::getWinner() == Player::Result_winner::PLAYER_1_WON){
		//	sentence = "Player 1 Won!!!";
		//}
		//else if (Player::getWinner() == Player::Result_winner::PLAYER_2_WON){
		//	sentence = "Player 2 Won!!!";
		//}
		//else{
		//	sentence = "It was a tie";
		//}

		writeOnScreenLocation(Lines::LINE_ONE_RIGHT, sentence + " WELL DONE!");
		action = GameManager::LevelOptions::NEXT_LEVEL;
	}
	else if(escapePressed) {
		action = 0;
		// TODO: print here the sub menu options to the proper place in screen
		CleanTopOfScreen();
		clear_screen();
		gotoxy(0, 3);
		/*cout << endl << endl << endl;*/

		cout << "1. exit application" << endl;
		cout << "2. back to main menu" << endl;
		cout << "3. continue" << endl;
		cout << "4. replay level" << endl;
		cout << "5. next level" << endl;

		do {
			action = _getch();
		} while(!GameManager::LevelOptions::isValidOption(action));
	}
	// end of esc pressed
	// TODO: clear the sub menu options from screen
	return action;
}

bool GameManager::doIteration()
{
	unsigned int sleepLength = clockCycleInMillisec/iterationsPerClockCycle;
	for(unsigned int i=0; i<iterationsPerClockCycle-1; ++i) {
		Sleep(sleepLength);
		actualGame.doSubIteration(currentLevel);
	}
	return doInputIteration();
}

bool GameManager::doInputIteration()
{
	list<char> keyHits(KEYBOARD_HIT_LOOP); // set vector initialize size to the max key strokes that we may collect
	bool shouldContinue = true;
	// get keyboard input in a loop, to get enough keyboard hits
	unsigned int sleepLength = clockCycleInMillisec/iterationsPerClockCycle / KEYBOARD_HIT_LOOP;
	for(unsigned int i=0; i<KEYBOARD_HIT_LOOP; ++i) {
		Sleep(sleepLength);
		if (_kbhit()) {
			char ch = _getch();
			if(ch == ESC) {
				// ESC pressed
				shouldContinue = false;
			}
			else {
				// we got keyHits byref, so we actually set input into the original list sent here
				keyHits.push_front(ch); // we want recent keys to come first, thus we use push_front
			}
		}
	}
	// send the keystrokes to the game
	// (even if ESC was hit, we may still have something in the keystrokes vector and should use it)
	actualGame.doIteration(keyHits, currentLevel);

	return shouldContinue;
}

