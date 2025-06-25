#include <string.h>
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

//enum ConsoleColor
//{
//	Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray,
//	LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
//};
//
//void SetColor(int text, int background)
//{
//	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
//}
//void f1()
//{
//	cout << "Function 1" << endl;
//}
//
//void f2()
//{
//	cout << "Function 2" << endl;
//}
//int f3(char k) {
//	cout << k << endl;
//	return 1;
//}
//
//char f1(char) {// ... }
//char f2(int) {// ... };
//void f3(float) {// ... };
//int* f4(char*) {// ... };
//char (*pt1)(int);
//char (*pt2)(int);
//void (*ptr3)(float) = f3;


int add(int n1, int n2) { return n1 + n2; }
int sbt(int n1, int n2) { return n1 - n2; }
int mult(int n1, int n2) { return n1 * n2; }
int divis(int n1, int n2) { return n1 / n2; }





int main()
{
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//enum - перечесляемый тип
	//enum Suit {CLUBS, DIAMODS, HEARTS, SPADES};
	//SetColor(1, 13);
	//Suit k1 = { Suit::DIAMODS };
	//cout <<static_cast<string> ( Suit::DIAMODS ) << endl;
	/*void (*pf1)();
	pf1 = f1;
	f1();
	(*pf1)();
	pf1 = f2;
	(*pf1)();*/
	/*int (*pf3)(char d) = f3;
	(*pf3)('A');*/
	/*int (*pf)(int s1, int s2);
	char ch;
	cin >> ch;
	switch (ch)
	{
	case '+':
		pf = add;
		break;
	case '-':
		pf = sbt;
		break;
	case '*':
		pf = mult;
		break;
	case '/':
		pf = divis;
		break;

	default:
		cout << "Error" << endl;
		break;
	}
	cout << (*pf)(3, 2) << endl;*/
	//pt1 = f1;
	//pt2 = f3;
	//pt1 = f4;
	//pt1 = f2;
	//pt2 = pt1;
	//char с = (*pt1)(44);
	//с = (*pt2)('\t');

	//int ar[] = { 2,6,7,9,8 };
	//int* par = ar;//    *(par+1)

	int (*par_f[4])(int, int) = { add, sbt, mult, divis };
	for (int i = 0; i < 4; i++)
	{
		cout << "Function" + i << endl;
		cout << par_f[i](10, 15) << endl;
	}



	system("pause");
}


//create
//print
//init ---- одномерный массив типа double
//sort
//delete