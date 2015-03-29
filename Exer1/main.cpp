//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// main.cpp
// --------
// This is the main entry point of the program.
// Keep the main short!
//
// Author: Amir Kirsh
// First version: 2014-12-09
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// In the file itself, add above each change/addition a remark saying: "NEW CODE EX1, author=<name>, date=<YYYY-MM-DD>"
// and close it at the end with a remark saying "END of NEW CODE EX1" 
// Add these remarks also at the beginning and end of any new file that you add.
//
// Below lines are an example, replace it with your own if you make any changes (one entry per relevant change!)
// NOTE: the lines shall be added in the file that was changed only!
//
// 2014-12-15     Yovav Ben-Shimshon      implemented the menu
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#include <iostream>
#include <time.h>
#include "GameManager.h"
#include "io_utils.h"
#include "TheMathGame.h"
#include "Player.h"

using namespace std;

// this is for example only!
// delete this class and implement your own properly!
//class TheMathGame: public ISpecificGame
//{
//public:
//	virtual bool isLevelDone()const{return false;}
//	virtual bool hasNextLevel()const{return true;}
//	virtual void startLevel(){}
//	virtual void doIteration(const list<char>& keyHits){}
//	virtual void doSubIteration(){}
//};


//==========================
//  M  A  I  N
//==========================
int main(){

	//for (size_t i = 0; i < 10; i++)
	//{
	//	CreateExercise  c = CreateExercise(5);

	//	unsigned int t1 = c.getHiddenValue();
	//	string t2 = c.getHiddenExercise();
	//	cout << t2 << "::::::::" << t1 << endl;
	//}
	
	clear_screen();
	hideCursor();
	srand((unsigned int)time(NULL));
	GameManager(TheMathGame(), 200, 2).run();
	return 0;
}
//==========================
// E n d   o f   M  A  I  N
//==========================
