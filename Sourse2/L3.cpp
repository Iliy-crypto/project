#include <string.h>
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

struct date
{
	int day;
	int weekday;
	string mon_name;
	int year;
};
void Print_date(date _d)
{
	cout << _d.year << "" << _d.mon_name << "" << _d.weekday << "" << _d.day << endl;
}




int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "ru");
	/*SetConsoleCP(1251);
	SetConsoleOutputCP(1251);*/
	
	date bd = { 10,2,"November",2025 };

	date d_exam = { 16,1,"June",2025 };
	cout << bd.mon_name << endl;
	cout << d_exam.day << endl;




	Print_date(bd);
	Print_date(d_exam);


	system("pause");
}

