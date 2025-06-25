#include <string.h>
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define N 2
using namespace std;

// 1 - Файловая переменная
// 2 - Открыть файл
// 3 - Операции с данными в файл
// 4 - Закрыть файл
struct  tag_book
{
	char name[100];
	char author[100];
	int year;
} books[N];

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	
	
	// 1.1 , 1.2

	//FILE* f = fopen("C:\\Курсы C ++\\Sourse2\\Sourse2\\text.txt", "w");

	//if (!f) cout << "file not open" << endl;
	//else
	//{
	//	cout << "file opened" << endl;
	//	fprintf(f, "hello,students");
	//	fclose(f);
	//}
	//cout << "++++++++++++++++++++++++++++++++++" << endl;

	////2.2

	//f = fopen("C:\\Курсы C ++\\Sourse2\\Sourse2\\text.txt", "r");
	//if (!f) cout << "file not open" << endl;
	//else
	//{
	//	/*string s;
	//	fscanf(f, "%s", s);
	//	cout << s << endl;*/
	//}


	// 3

	/*FILE* f = fopen("filetest.txt", "w");
	if (!f)
		cout << "error" << endl;
	else
	{
		cout << "file opened\n";
		for (int i = 0;i < 16;i++)
		{
			fprintf(f, "%#d\t %#o\t %#X\n", i, i, i);
		}
		fclose(f);
		cout << "file closed" << endl;
	}
	f = fopen("filetest.txt", "r");
	if (!f)
		cout << "error" << endl;
	else
	{
		char* s;
		cout << "file opened for read\n" << endl;
		char buf[128];
		do
		{
			s = fgets(buf, sizeof(buf), f);
			cout << buf << endl;
		} while (s);
		fclose(f);
		cout << "\n\nfile close\n\n";
	}*/


	FILE* fp; //=/* fopen("my_file.txt", "w");*/

	/*for (int i = 0; i < N; i++)

	{

		scanf("%s", books[i].name);

		scanf("%s", books[i].author);

		scanf("%d", &books[i].year);

	}

	for (int i = 0; i < N; i++)

	{

		puts(books[i].name);

		puts(books[i].author);

		printf("%d\n", books[i].year);

	}

	for (int i = 0; i < N; i++)

		fprintf(fp, "%s %s %d\n", books[i].name, books[i].author, books[i].year);

	fclose(fp);

	cout << "------------------------------" << endl;*/
	fp = fopen("my_file.txt", "r");

	for (int i = 0; i < N; i++)

		fscanf(fp, "%s %s %d\n", books[i].name, books[i].author, &books[i].year);

	fclose(fp);

	printf("------------------------------------------------\n");

	for (int i = 0; i < N; i++)

	{

		puts(books[i].name);

		puts(books[i].author);

		printf("%d\n", books[i].year);

	}





}

