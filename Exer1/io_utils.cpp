#include "io_utils.h"
#include "Color.h"

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

void writeOnTopOfScreen(string sentence){
	// Go to the top of the screen
	gotoxy(0, 0);

	// Clean the 2 first lines
	for (int j = 0; j < AMOUNT_OF_INSTRUCTIONS_LINE; j++)
	{
		for (int i = 0; i < LENGH_OF_LINE; i++)
		{
			cout << "";
		}
	}

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


