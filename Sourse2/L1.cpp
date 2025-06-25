#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<stdlib.h>

using namespace std;

int main() 
{
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//setlocale(LC_ALL, "ru");

	//5

	//char line[80];
	//cin >> line;
	//gets_s(line);
	//cout << line << endl;
	//puts(line);

	//6

	//char* str1 = new char[128];
	//cin.getline(str1, 128);
	//cout << str1 << endl;
	//cout << sizeof(str1) << endl;

	//7

	//char* str1 = new char[128];
	//cin.getline(str1, 128);
	//int len = strlen(str1);
	//cout << len << endl;

	//8

	//_strupr(str1);
	//cout << str1 << endl;

	//9

	////_strrev(str1);
	//cout << str1 << endl;

	//10

	char s1[] = "Charnogor";
	char s2[] = "Eleonora";
	char s3[] = "Yirievna";
	int size = strlen(s1) + strlen(s2) + strlen(s3);
	char* mas = new char[size];
	strcpy(mas, s1);
	strcat(mas, " ");
	strcat(strncat(mas, s2, 1), ".");
	strcat(strncat(mas, s3, 1), ".");
	cout << mas << endl;

	

}

