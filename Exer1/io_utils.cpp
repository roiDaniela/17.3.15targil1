#include "io_utils.h"
#include "Color.h"
#include <map>
using namespace std;

#ifndef WINDOWS
	void gotoxy(int x, int y) {}
	int _getch(void){return 0;}
	int _kbhit(void){return 0;}
	void Sleep(unsigned long){}
	void setTextColor(int color){}
	void hideCursor(){}
	void clear_screen(){}
#else

void RefreshScreen( const map<Point, int>& DataBase ){
	for (map<Point, int>::const_iterator iter = DataBase.cbegin(); iter != DataBase.cend(); iter++){
		gotoxy(iter->first);
		cout << iter->second;
	}
}

void CleanTopOfScreen(){
	// Go to the top of the screen
	gotoxy(0, 0);

	// Clean the 2 first lines
	for (int j = 0; j < AMOUNT_OF_INSTRUCTIONS_LINE; j++)
	{
		for (int i = 0; i < LENGH_OF_LINE; i++)
		{
			cout << " ";
		}
	}

	gotoxy(0, 3); // back to start location
}

void writeOnScreenLocation(Lines line_location, std::string sentence){
	Point* location = NULL;

	switch (line_location)
	{
	case Lines::LINE_ONE_LEFT:{
		location = new Point(40,0);

		break;
	}
	case Lines::LINE_ONE_RIGHT:{
		location = new Point(0, 0);

		break;
	}
	case Lines::LINE_TWO_RIGHT:{
		location = new Point(0, 1);

		break;
	}
	case Lines::LINE_TWO_LEFT:{
		location = new Point(40, 1);

		break;
	}
	case Lines::LINE_THREE_RIGHT:{
		location = new Point(0, 2);

		break;
	}
	case Lines::LINE_THREE_LEFT:{
		location = new Point(40, 2);

		break;
	}
	case Lines::LINE_ONE_MIDDLE:{
		location = new Point(20, 0);

		break;
	}
	default:
		break;
	}

	gotoxy(*location);

	// Clean the 2 first lines
	//for (int j = 0; j < AMOUNT_OF_INSTRUCTIONS_LINE - 1; j++)
	//{
	for (int i = location->getX(); i < (location->getX() + LENGH_OF_LINE / 2); i++)
		{
			cout << " ";
		}
	//}

	gotoxy(*location);
	cout << sentence;
	gotoxy(0, 3);
}
void writeOnThirdRowOfScreen(string sentence){
	// Go to the top of the screen
	gotoxy(0, 3);

	// Clean the 2 first lines
	for (int i = 0; i < LENGH_OF_LINE; i++)
	{
		cout << " ";
	}

	gotoxy(0, 3);
	cout << sentence;
}

// My aading 22.3.15
void gotoxy(const Point& p){
	gotoxy(p.getX(), p.getY());
}

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout<<flush;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

void setTextColor(Color colorToSet){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}

void hideCursor()
{
	 HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	 CONSOLE_CURSOR_INFO CURSOR;
	 CURSOR.dwSize = 1;
	 CURSOR.bVisible = FALSE;
	 SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}

void clear_screen()
{
	system("cls");
}

#endif


