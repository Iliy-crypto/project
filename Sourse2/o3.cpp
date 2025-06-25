//#include "myheader.h"
#include <conio.h>
#include <iomanip>
#include <iostream> 
#include <windows.h>
using namespace std;
// 1. добавить conio.h
// 2. добавить gotoxy
void gotoxy(short x, short y) // аналог борландовской gotoxy
{
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD  coord = { x, y };
	SetConsoleCursorPosition(StdOut, coord);
}
enum { lleft = 75, down = 80, up = 72, rright = 77 };

void main()
{
	int move, x(10), y(10), smile(1);
	do {
		//system("cls");
		move = getch();
		switch (move)
		{
		case lleft:		x--; break;
		case rright:	x++; break;
		case up:		y--; break;
		case down:		y++; break;
		}
		gotoxy(x, y);
		cout << (char)smile;
	} while (true);
}