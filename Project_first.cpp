#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h> 

enum ConsoleColor // цвета которыми можно окрашивать
{
	Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray,
	LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};

void SetColor(int text, int background) //функция с помощью которой происходит изменение цвета текста
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //дескриптор активного окна

void gotoxy(short x, short y) //аналог борландовской gotoxy
{
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD  coord = { x, y };
	SetConsoleCursorPosition(StdOut, coord);
}
enum { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Q = 113 };




void SetCursor(int x, int y) //функция для того чтобы устанавливать позицию курсора в консоли по оси Х и Y
{
	COORD myCoords = { x,y }; //инициализация координат
	SetConsoleCursorPosition(hStdOut, myCoords); //способ перемещения курсора на нужные координаты
}

using namespace std;


struct Ships //структура характеристик кораблика
{
	int deck = { 0 }; //количество палуб
	bool horizontal = true; //положение (изначально - горизонтальное)
	bool alive = true; //проверка на то, унчитожен ли кораблик или нет
	int x, y; //позиции кораблика по "x" и "y"
};

void explosion(Ships* characteristic, int ship_pos[12][24], int plus, int& end); //Уничтожение кораблкиков и определение победителя в игре

void LoadCharactShips(Ships* characteristic); //присвоение палуб в соответствии с номером кораблика

void auto_arrangement(Ships* characteristic, int ship_pos[12][24], int plus); //aвтоматическая расстановка корабликов

void PaintPos(int mas[12][24], int x, int num_color); //прорисовка игровой карты в соответсвии с положением поставленных корабликов

void Title(); //функция которая будет показана игроку самая первая

void CreatField(int speed, int X, int num_color); //Функция, благодаря которой будет отрисовываться игровое поле

void Paint(char variant[3][30], int T); //меню выбора расстановки 

void Text(int num);

int calculateScore(int hits, int misses, int& remainingPenalty) {
	int score = 0;
	int totalPenalty = misses * 5; // Общий штраф
	remainingPenalty = totalPenalty; // Оставшийся штраф

	// Награда за попадания
	for (int i = 0; i < hits; i++) {
		int bonus = 5 * ((i / 5) + 1);

		// Если есть невычтенные штрафы, сначала уменьшаем их
		if (remainingPenalty > 0) {
			if (bonus <= remainingPenalty) {
				remainingPenalty -= bonus; // Полностью убираем штраф на размер бонуса
				bonus = 0; // Бонус полностью ушел на штраф
			}
			else {
				bonus -= remainingPenalty; // Часть бонуса ушла на штраф
				remainingPenalty = 0; // Штраф полностью погашен
			}
		}

		score += bonus;
	}

	return score;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	char variant[3][30] = { "АВТОМАТИЧЕСКАЯ РАССТАНОВКА","РУЧНАЯ РАССТАНОВКА","ВЫХОД" };
	int ship_pos[12][24] = { 0 };
	int enemy_ship_pos[12][24] = { 0 };
	int retry; //переменная для повторения игры
	int playerHits = 0, computerHits = 0;
	int playerMisses = 0, computerMisses = 0;
	int playerRemainingPenalty = 0;
	int computerRemainingPenalty = 0;
	do
	{
		Ships* characteristic = new Ships[20]; //создаём 10 корабликов
		LoadCharactShips(characteristic); //загрука характеристик корабликов (изначальное положение и количество палуб)
		int key = 1, y = 1, x = 2, num = 0, change = 1, A = 0, xx = 37, yy = 2, up = 0, down = 0, over = 0;
		bool manual_placement = true, your_turn = 0 + rand() % 2, start = false, control = false;
		/*
		key - переменная для записи нажатой клавиши
		start - переменная для проверки на начало боя
		speed - скорость прорисовки игрового поля
		А - дополнительная переменная для меню
		SN - переменная для того чтобы запоминать какой кораблки мы стараемся добить.
		up - переменная которая поможет правильно добивать наши кораблики
		down - переменная которая поможет правильно добивать наши кораблики
		xx - дополнительная перемнная для записи положения курсора на вражеском поле
		yy - дополнительная перемнная для записи положения курсора на вражеском поле
		y - позиция по Y
		x - позиция по X
		change - номер расстановки который будет использован
		num - номер кораблкиа
		manual_placement - тип расстановки который будет использован
		*/

		Title(); //Выводим надпись "МОРСКОЙ БОЙ" на экран
		Sleep(1500); //ждём 1.5 секунды
		SetColor(White, Black);
		system("cls");
		CreatField(1, 0, 9); //создаём игровое поле
		Paint(variant, change);
		do //запускаем цикл
		{
			key = _getch();
			switch (key)
			{
			case Up: //если нажали "Стрелочка вверх"
				if (y > 0)
				{
					y--;
					change = y; //выбранный пункт
					Paint(variant, change); //вывод пунктов на экран
				}
				break;
			case Down: //если нажали "Стрелочка вниз"
				if (y < 2)
				{
					y++;
					change = y;
					Paint(variant, change);
				}
				break;
			case Enter:
				do
				{
					switch (change)
					{
					case 0:
						manual_placement = false; //автоматическая расстановка
						A++; //чтобы завершить цикл
						break;
					case 1:
						manual_placement = true; //ручная расстановка
						A++;
						y++;
						break;
					case 2:
						system("cls");
						SetColor(White, Red);
						SetCursor(24, 12);
						cout << "ДО СВИДАНИЯ";
						SetColor(Black, Black);
						return 0;
						system("pause");
					}
				} while (key != Enter);
			}
		} while (A < 1);
		system("cls");
		CreatField(0, 0, 9);
		x = 2, y = 2;
		if (manual_placement == false) //если выбрана автоматическая расстановка
		{
			auto_arrangement(characteristic, ship_pos, 0); //передаём необходимые значения для того, чтобы автоматически расставить кораблки
			PaintPos(ship_pos, 2, 0); //перерисовываем игровую локации с учетём внесенных изменений
			start = true; //начинаем игру
		}
		else if (manual_placement == true && num < 10) //ручная расстановка
		{
			do //запускаем цикл в котором при нажатии на ту или иную клавишу будем делать то или иное дейстивие
			{
				PaintPos(ship_pos, 2, 0);
				SetCursor(x, y); //ставим курсор на позицию изменяемых ниже переменных (X, Y)
				SetColor(Black, Black);
				if (characteristic[num].horizontal == true) //если кораблик имеет горизонтальное положение
				{
					for (size_t i = 0; i < characteristic[num].deck; i++) //запускаем цикл который будет отрисовыввать кораблик с нужным колличеством палуб
					{
						cout << "++"; //2 "+" так как одна клеточка в ширину в игре равна 2-ум клеточкам в ширину в консоли
					}
				}
				else if (characteristic[num].horizontal == false)
				{
					y += characteristic[num].deck; //изменяем позицию по "y" на то, сколько палуб у кораблика
					for (size_t i = 0; i < characteristic[num].deck; i++)  //запускаем цикл который будет отрисовывать кораблик с нужным количеством палуб
					{
						cout << "++"; //2 "+" так как одна клеточка в ширину в игре равна 2-ум клеточкам в ширину в консоли
						y--; //спускаемся вниз на одну клеточку
						SetCursor(x, y); //устанавливаем позицию на одну клеточку ниже и на изначальное по Х
					}
				}
				key = _getch();//функция возвращает номер нажатой клавиши
				switch (key) //Выполняем различные функции в соответствии с нажатой клавишью
				{
				case Left: //если нажали "Стрелочка влево"
					if (x > 3) //позиция до которой разрешено перемещение влево
					{
						x -= 2; //меняем значение по Х на -2 так как одна клеточка в игре равна двум в консоли
					}
					break;
				case Right: //если нажали "Стрелочка вправо"
					if (characteristic[num].horizontal == true) //Если кораблик имеет горизонтальное положение
					{
						if (x < 22 - characteristic[num].deck * 2) //проверяем, не достиг ли он позиции до которой ему можно передвигаться(чтобы он не вышел за границы поля)
						{
							x += 2; //меняем значение переменной Х на +2 так как одна клеточка в игре равна двум в консоли
						}
					}
					else  //Если кораблик имеет вертикальное положение
					{
						if (x < 20)
						{
							x += 2;
						}
					}
					break;
				case Up: //если нажали "Стрелочка вверх"
					if (y > 2) //позиция до которой разрешено перемещение вверх
					{
						y--;  //меняем значение по Y на -1
					}
					break;
				case Down: //если нажали "Стрелочка вних"
					if (characteristic[num].horizontal == false) //Если кораблик имеет вертикальное положение
					{
						if (y < 12 - characteristic[num].deck) //проверяем, не достиг ли он позиции до которой ему можно передвигаться (так как он 4-х палубный, и его нужно ограничивать на 3 клеточки ранее)
						{
							y++;  //меняем значение по Y на +1
						}
					}
					else
					{
						if (y < 11) // проверяем, не достиг ли он позиции до которой ему можно передвигаться(чтобы он не вышел за границы поля)
						{
							y++;
						}
					}
					break; //закрыли этот кейс
				case Q: //если нажали "Q"
					characteristic[num].horizontal = !characteristic[num].horizontal; //изменяем ориентацию кораблика на противоположную
					if (characteristic[num].horizontal == false && y + characteristic[num].deck >= 13)
						//проверяем, заденет ли кораблик границу по вертикале при перевороте, если его не отодвинуть
					{
						y -= y + characteristic[num].deck - 12; //если да, то заранее изменем его положение, чтобы он не прошел сковзь границы поля по вертикали
					}
					else if (characteristic[num].horizontal == true && x + characteristic[num].deck * 2 >= 24)

					{
						x -= (x + characteristic[num].deck * 2) - 22;
					}
					for (size_t i = 0; i < 10 - num; i++) //изменяем ориентацию так же и для последующих корабликов
					{
						characteristic[num + i].horizontal = characteristic[num].horizontal; // заранее изменяем положение следующего кораблика на то, которое мы выбрали сейчас
					}
					break;
				case Enter: //если нажали "Enter"
					if (characteristic[num].horizontal == true && ship_pos[y - 1][x] == 0 && ship_pos[y - 1][x + characteristic[num].deck * 2 - 2] == 0)
					{
						characteristic[num].x = x + 2, characteristic[num].y = y;
						for (size_t q = 0; q < 3; q++)
						{
							for (size_t w = 1; w < characteristic[num].deck * 3 + 1; w++)
							{
								ship_pos[y - 2 + q][x - 3 + w] = 1;
							}
						}
						for (int g = 0; g < 2 * characteristic[num].deck; g++)
						{
							ship_pos[y - 1][x + g] = 13 - num;
						}
						num++;
					}
					if (characteristic[num].horizontal == false && ship_pos[y - 1][x] == 0 && ship_pos[y + characteristic[num].deck - 2][x] == 0)
					{
						characteristic[num].x = x + 2, characteristic[num].y = y;
						for (size_t q = 0; q < characteristic[num].deck + 2; q++)
						{
							for (size_t w = 0; w < 6; w++)
							{
								ship_pos[y - 2 + q][x - 2 + w] = 1;
							}
						}
						for (int g = 0; g < characteristic[num].deck; g++)
						{
							for (int n = 0; n < 2; n++)
							{
								ship_pos[y - 1 + g][x + n] = 13 - num;
							}
						}
						num++; //переходим к следующему кораблику
					}
				}
				start = true;//запускаем игру
			} while (num <= 9); //цикл работает до тех пор пока количество расставленных корабликов не равно 10
		}
		Sleep(20);
		CreatField(1, 35, 4); //создаём игровое поле
		auto_arrangement(characteristic, enemy_ship_pos, 10); //автоматическая расстанвока для вражеских корабликов
		PaintPos(enemy_ship_pos, 37, 15); //отрисовка вражеских кораблей/поля
		do
		{
			if (your_turn == true) //если моя очередь атаковать
			{
				do //запускаем цикл, в котором при нажатии на ту или иную клавишу будем делать то или иное дейстивие
				{
					x = xx, y = yy; //переменная, которая будет запоминать где находился курсор 
					PaintPos(enemy_ship_pos, 37, 15); //перерисовываем игровую локации с учётом внесенных изменений
					SetColor(DarkGray, DarkGray); //устанавливаем черный цвет так как таким цветом будет выводиться кораблик
					SetCursor(x, y); //ставим курсор на позицию изменяемых ниже переменных (X, Y)
					cout << "++"; //2 "+" так как одна клеточка в ширину в игре равна 2-ум клеточкам в ширину в консоли
					key = _getch();//функция возвращает номер нажатой клавиши
					switch (key) //Выполняем различные функции в соответствии с нажатой клавишью
					{
					case Left: //если нажали "Стрелочка влево"
						if (x > 38) //позиция, до которой разрешено перемещение в лево
						{
							x -= 2; //меняем значение по Х на -2 так как одна клеточка в игре равна двум в консоли
							xx = x; //запоминаем положение курсора
						}
						break;
					case Right: //если нажали "Стрелочка вправо"
						if (x < 55) // проверяем не достиг ли он позиции, до которой ему можно передвигаться(чтобы он не вышел за границы поля)
						{
							x += 2;
							xx = x;
						}
						break;
					case Up: //если нажали "Стрелочка вверх"
						if (y > 2) //позиция, до которой разрешено перемещение вверх
						{
							y--;  //меняем значение по Y на -1
							yy = y;
						}
						break;
					case Down: //если нажали "Стрелочка вних"
						if (y < 11) //позиция до которой разрешено перемещение вниз
						{
							y++;  //меняем значение по Y на +1
							yy = y;
						}
						break;
					case Enter:
						if (enemy_ship_pos[y - 1][x - 35] >= 4) //проверяем позицию, по которой мы выстрельнули на наличие корабликов
						{
							for (size_t i = 0; i < 2; i++)
							{
								enemy_ship_pos[y - 1][x - 35 + i] = 3;
								explosion(characteristic, enemy_ship_pos, 10, over); //проверяем на уничтожение
							}
							playerHits++;
							Text(9); //вывод реплики на экран
							Sleep(700); //небольшая пауза
						}
						else if (enemy_ship_pos[y - 1][x - 35] < 2) //Если на позиции, по которой был произведён огонь, ничего нету 
						{
							for (size_t i = 0; i < 2; i++) //если это так то мызаменяем в клеточке номерок кораблика на "2"
							{
								enemy_ship_pos[y - 1][x - 35 + i] = 2; // изменяем значение	
							}
							playerMisses++;
							Text(5); //вывод реплики на экран
							your_turn = false; //очередь атаки противника
						}
						break;
					}
				} while (key != Enter); //выполнять код который демонстрируется в цикл до тех пор пока не нажата клавиша "Enter"
			}
			if (your_turn == false) //если ход противника
			{
				Sleep(700); //небольшая пауза
				Text(0); //вывод реплики на экран
				PaintPos(ship_pos, 2, 0); //перерисовываем наше поле
				Sleep(700); //небольшая пауза
				x = (2 + rand() % 10) * 2, y = 2 + rand() % 10; //случайным образом выдаём кооординату по которой будет происходить атака
				if (ship_pos[y - 1][x - 1] >= 4) //проверяем позицию по которой мы выстрельнули на наличие корабликов
				{
					for (size_t i = 0; i < 2; i++) //если это так, то мы заменяем в клеточке номерок кораблика на "3"
					{
						ship_pos[y - 1][x - 2 + i] = 3;  // изменяем значение
						explosion(characteristic, ship_pos, 0, over); //проверяем на уничтожение
					}
					computerHits++;
					Text(2);
					Sleep(700); //небольшая пауза
				}
				else if (ship_pos[y - 1][x - 1] <= 2) //Если на позиции,по которой был произведён огонь, ничего нету 
				{
					for (size_t i = 0; i < 2; i++) //если это так, то мы заменяем в клеточке номерок кораблика на "2"
					{
						ship_pos[y - 1][x - 2 + i] = 2; //изменяем значение
					}
					computerMisses++;
					Text(1);
					Sleep(500); //небольшая пауза
					Text(4);
					your_turn = true; //очередь атаки игрока

				}
			}
			int playerScore = calculateScore(playerHits, playerMisses, playerRemainingPenalty);
			int computerScore = calculateScore(computerHits, computerMisses, computerRemainingPenalty);
			cout << "\n\n\nТекущие очки:\n";
			cout << "Вы: " << playerScore << " (попадания: " << playerHits << ", промахи: " << playerMisses << ")\n";
			cout << "ваши штрафы: -" << playerRemainingPenalty << endl;
			cout << "Компьютер: " << computerScore << " (попадания: " << computerHits << ", промахи: " << computerMisses << ")\n";
			cout << "штрафы компьютера: -" << computerRemainingPenalty << endl;
		} while (over == 0);
		PaintPos(ship_pos, 2, 0);
		PaintPos(enemy_ship_pos, 37, 15); //перерисовываем игровую локации с учетём внесенных изменений (поставили кораблик)
		if (over == 2)
		{
			Text(7); //выигрыш
			int playerScore = calculateScore(playerHits, playerMisses, playerRemainingPenalty);
			int computerScore = calculateScore(computerHits, computerMisses, computerRemainingPenalty);
			cout << endl << endl << endl;
			cout << "\n============================================\n";
			cout << "           ФИНАЛЬНАЯ СТАТИСТИКА\n";
			cout << "============================================\n";
			cout << "ИГРОК:\n";
			cout << "Попадания: " << playerHits << " (награда: +" << playerScore + playerRemainingPenalty << ")\n";
			cout << "Промахи: " << playerMisses << " (штраф: -" << playerMisses * 5 << ")\n";
			cout << "Окончательный штраф: -" << playerRemainingPenalty << endl;
			cout << "ФИНАЛЬНЫЙ СЧЕТ: " << playerScore << " баллов\n";
			cout << "________________________________________________\n";
			cout << "КОМПЬЮТЕР:\n";
			cout << "Попадания: " << computerHits << " (награда: +" << computerScore + computerRemainingPenalty << ")\n";
			cout << "Промахи: " << computerMisses << " (штраф: -" << computerMisses * 5 << ")\n";
			cout << "Окончательный штраф: -" << computerRemainingPenalty << endl;
			cout << "ФИНАЛЬНЫЙ СЧЕТ: " << computerScore << " баллов\n";
			cout << "============================================\n";
		}
		else
		{
			Text(3); //проигрыш
			int playerScore = calculateScore(playerHits, playerMisses, playerRemainingPenalty);
			int computerScore = calculateScore(computerHits, computerMisses, computerRemainingPenalty);
			cout << "\n\n\n\n\n============================================\n";
			cout << "           ФИНАЛЬНАЯ СТАТИСТИКА\n";
			cout << "============================================\n";
			cout << "ИГРОК:\n";
			cout << "Попадания: " << playerHits << " (награда: +" << playerScore + playerRemainingPenalty << ")\n";
			cout << "Промахи: " << playerMisses << " (штраф: -" << playerMisses * 5 << ")\n";
			cout << "Окончательный штраф: -" << playerRemainingPenalty << endl;
			cout << "ФИНАЛЬНЫЙ СЧЕТ: " << playerScore << " баллов\n";
			cout << "________________________________________________\n";
			cout << "КОМПЬЮТЕР:\n";
			cout << "Попадания: " << computerHits << " (награда: +" << computerScore + computerRemainingPenalty << ")\n";
			cout << "Промахи: " << computerMisses << " (штраф: -" << computerMisses * 5 << ")\n";
			cout << "Окончательный штраф: -" << computerRemainingPenalty << endl;
			cout << "ФИНАЛЬНЫЙ СЧЕТ: " << computerScore << " баллов\n";
			cout << "============================================\n";
		}
		Sleep(2000);
		Text(11);
		SetCursor(22, 16);
		SetColor(White, Black);
		cout << "0 - НЕТ; 1 - ДА" << endl;
		SetCursor(22, 17);
		cin >> retry;
		system("cls");
	} while (retry); //Повторяем игру, пока не напишем '0'
	{
		SetColor(White, Red);
		SetCursor(24, 12);
		cout << "ДО СВИДАНИЯ";
		SetColor(Black, Black);
		return 0;
		system("pause");
	}
}

void explosion(Ships* characteristic, int ship_pos[12][24], int plus, int& end) //Уничтожение кораблкиков и определение победителя в игре
{
	int A = 0; //переменная для правильной зарисовки границы вокруг взоравнного кораблика
	int B = 13; //переменная, которая будет помогать указывать на нужный кораблик
	int C = 0; //переменная, которая хранит количество уничтоженных корабликов (если = 10, то игра завершается)
	bool alive = false; //переменная с помощью которой мы будем проверять уничтожение корабликов
	for (size_t n = 13; n > 3; n--) //проверяем все номерки корабликов на наличие их в массиве
	{
		for (size_t i = 1; i < 11; i++)
		{
			for (size_t r = 2; r < 22; r++)
			{
				if (ship_pos[i][r] == n) //проверяем, есть ли в массиве хоть один номерок с корабликом
				{
					alive = true; //в случае успеха - кораблик жив/ранен
					i = 11; //меняем значение чтобы перейти к следуещему номерку
					break;
				}
			}
		}
		if (alive == false) //если номерок найден не был, то говорим, что кораблик которому был присвоен этот номер уничтожен
		{
			characteristic[B - n + plus].alive = false;
		}
		else
		{
			alive = false;
		}
	}
	for (size_t i = plus; i < 10 + plus; i++) //запускаем цикл, в котором будем проверять все кораблики одной команды на уничтожение
	{
		if (i == 0 || i == 10) //для 4-х палубных
		{
			A = 0; //меняем значение переменной для правильной отрисовки
		}
		else if (i == 1 || i == 2 || i == 11 || i == 12)  //для 3-х палубных
		{
			A = 1;
		}
		else if (i > 2 && i < 6 || i > 12 && i < 16)  //для 2-х палубных
		{
			A = 2;
		}
		else  //для 1-о палубных
		{
			A = 3;
		}
		if (characteristic[i].alive == false) //если данный кораблик уничтожен
		{
			if (characteristic[i].horizontal == true) //если он имеет горизонтальное положение
			{
				for (size_t q = 0; q < 3; q++) //выполняем нижеуказанный код 3 раза, так как нам необходимо окупировать кораблик чтобы они не стояли вполтную к друг другу
				{
					for (size_t w = 0; w < characteristic[i].deck * 3 + A; w++) //выполняем нижеуказанный код нужное количество раз (для каждого отдельно считаем), чтобы "окупировать" уничтоженный кораблик
					{
						ship_pos[characteristic[i].y - 2 + q][characteristic[i].x - 4 + w] = 2; //меняем значение "окупируемых" позиций в двумерном массиве который будем прверять на различные цифорки, на "2" (промах)

					}
				}
				for (size_t g = 0; g < 2 * characteristic[i].deck; g++) //выполняем нижеуказанный код нужное количество раз (для каждого отдельно считаем), чтобы выделить уничтоженный кораблик
				{
					ship_pos[characteristic[i].y - 1][characteristic[i].x - 2 + g] = 3; //меняем значение "окупируемых" позиций в двумерном массиве который будем прверять на различные цифорки, на "3" (попадание)
				}
			}
			else if (characteristic[i].horizontal == false)  //если он имеет вертикальное положение
			{
				for (size_t q = 0; q < characteristic[i].deck + 2; q++)
				{
					for (int w = -4; w < 2; w++)
					{
						ship_pos[characteristic[i].y - 2 + q][characteristic[i].x + w] = 2;
					}
				}
				for (int g = 0; g < characteristic[i].deck; g++)
				{
					for (int n = -2; n < 0; n++) //выполняем нижеуказаныый код 2 раза так как нам нужно поменять значения в массиве для 2-ух клеточек (одной палубы)
					{
						ship_pos[characteristic[i].y - 1 + g][characteristic[i].x + n] = 3;
					}
				}
			}
			C++; // увеличиваем значение счётчика уничтоженных корабликов на 1
		}
	}
	if (C == 10 && plus == 0) //если все наши кораблики уничтожены
	{
		end = 1; //завершаем игру (поражение)
	}
	else if (C == 10 && plus == 10) //если все кораблики врага уничтожены
	{
		end = 2; //завершаем игру (победа)
	}
	else //иначе
	{
		C = 0; //онулируем счетчик уничтоженных корабликов
	}
}
void LoadCharactShips(Ships* characteristic) //присвоение палуб в соответствии с номером кораблика
{
	for (size_t i = 0; i < 20; i++)
	{
		if (i == 0 || i == 10)
		{
			characteristic[i].deck = 4; //делаем кораблик с 4-мя палубами
		}
		else if (i > 0 && i <= 2 || i > 10 && i <= 12)
		{
			characteristic[i].deck = 3; //делаем кораблик с 3-мя палубами
		}
		else if (i > 2 && i <= 5 || i > 12 && i <= 15)
		{
			characteristic[i].deck = 2; //делаем кораблик с 2-мя палубами
		}
		else if (i > 5 && i <= 9 || i > 15 && i <= 19)
		{
			characteristic[i].deck = 1; //делаем кораблик с 1-ой палубой
		}
	}
}
void auto_arrangement(Ships* characteristic, int ship_pos[12][24], int plus) //aвтоматическая расстановка корабликов
{
	int y, x, ship = plus; //переменная для координат и номера кораблика 
	while (ship < plus + 10)
	{
		characteristic[ship].horizontal = 0 + rand() % 2; //присваиваем рандомную ориентацию
		y = 2 + rand() % 9, x = (1 + rand() % 9) * 2; //присваиваем рандочные координаты (в рамках игровой зоны)
		if (characteristic[ship].horizontal == false && y + characteristic[ship].deck >= 13) //проверяем заденит ли кораблик границу по вертикале при перевороте, если его не отодвинуть
		{
			y -= y + characteristic[ship].deck - 12; //если да, то заранее изменяем его положение, чтобы он не прошел сковзь границы поля по вертикали
		}
		else if (characteristic[ship].horizontal == true && x + characteristic[ship].deck * 2 >= 24) //проверяем заденит ли кораблик границу по вертикале при перевороте, если его не отодвинуть
		{
			x -= (x + characteristic[ship].deck * 2) - 22; //если да, то заранее изменем его положение чтобы он не прошел сковзь границы поля по вертикали
		}
		if (characteristic[ship].horizontal == true && ship_pos[y - 1][x] == 0 && ship_pos[y - 1][x + characteristic[ship].deck * 2 - 2] == 0) // проверяем имеет ли кораблик горизонтальное положение и нет ли ничего на позициях куда он будет устанавливаться
		{
			characteristic[ship].x = x + 2, characteristic[ship].y = y; //запоминаем координаты первой палубы у каждого кораблика, чтобы в дальнейшем правильно их взрывать
			for (size_t q = 0; q < 3; q++)
			{
				for (size_t w = 1; w < characteristic[ship].deck * 3 + 1; w++)
				{
					ship_pos[y - 2 + q][x - 3 + w] = 1;
				}
			}
			for (int g = 0; g < 2 * characteristic[ship].deck; g++)
			{
				ship_pos[y - 1][x + g] = 13 - ship + plus;
			}
			ship++; //переходим к следующему кораблику
		}
		if (characteristic[ship].horizontal == false && ship_pos[y - 1][x] == 0 && ship_pos[y + characteristic[ship].deck - 2][x] == 0) // проверяем имеет ли кораблик горизонтальное положение и нет ли ничего на позициях, куда он будет устанавливаться
		{
			characteristic[ship].x = x + 2, characteristic[ship].y = y; //запоминаем координаты первой палубы у каждого кораблика, чтобы в дальнейшем правильно их взрывать
			for (size_t q = 0; q < characteristic[ship].deck + 2; q++)
			{
				for (size_t w = 0; w < 6; w++)
				{
					ship_pos[y - 2 + q][x - 2 + w] = 1; //меняем значение "окупируемых" позиций в двумерном массиве который будем прверять на различные цифорки, на "1" (окупируемая позиция живого кораблика)
				}
			}
			for (int g = 0; g < characteristic[ship].deck; g++)
			{
				for (int n = 0; n < 2; n++)
				{
					ship_pos[y - 1 + g][x + n] = 13 - ship + plus; //меняем значение позиций в двумерном массиве который будем прверять на различные цифорки, на "4-13" (номера корабликов)
				}
			}
			ship++; //переходим к следующему кораблику
		}
	}
}
void PaintPos(int mas[12][24], int x, int num_color) //прорисовка игровой карты в соответсвии с положением поставленных корабликов
{
	for (size_t i = 1; i < 11; i++)
	{
		int y = 1 + i; //уставнавливаем координаты по умолчанию 2 по Х и 2 по Y так как отрисовка поля должно начинаться там
		SetCursor(x, y); //перемещаем курсор на вышеуказанные позиции

		for (size_t g = 2; g < 22; g++)
		{
			if (mas[i][g] == 2) //если в массиве на этом месте находится "2"
			{
				SetColor(LightGray, LightGray); //рисуем серую клеточку
			}
			else if (mas[i][g] == 3) //если в массиве на этом месте находится "3"
			{
				SetColor(LightMagenta, LightMagenta); //рисуем клеточку малинового цвета
			}
			else if (mas[i][g] >= 4) //если в массиве на этом месте находится "4+"
			{
				SetColor(ConsoleColor(num_color), ConsoleColor(num_color)); //устанавливаем цвет корабликов (наши - черные / врага - белые)
			}
			else //в иных случаях рисуем белую клеточку
			{
				SetColor(White, White); //устанавливаем белый цвет так как таким цветом будет игровая локация на которой будут происходить основные действия
			}
			cout << "+"; //рисуем любой знак, из-за окраски он будет квадратиком
		}
		cout << "\n"; //переход на новую строку при отрисовки одной строки полностью
	}
}
void Title() //функция которая будет показана игроку самая первая
{
	SetColor(White, LightBlue);
	SetCursor(24, 12);
	cout << "МОРСКОЙ БОЙ";
}
void CreatField(int speed, int X, int num_color) //Функция, благодаря которой будет отрисовываться игровое поле
{
	SetCursor(X, 1); //Устанавливаем курсор на нужную позицию
	char mas[10] = { 'А','Б','В','Г','Д','Е','Ж','З','И','К' };
	SetColor(White, ConsoleColor(num_color)); //Смена цвета (буква - белый; заливка - красный/синий)
	int A = 0, B = 0; //переменные необходимые для правильной отрисовки игрового поля
	cout << "  " << mas[0]; //С помощью этого печатаем букву "А" и ставим в начале пробел чтобы было ровненько и красиво
	for (size_t i = 0; i < 12; i++)
	{
		if (B == 0)
		{
			SetCursor(X + 3, 1 + i);
			B++;
		}
		else
		{
			SetCursor(X, 1 + i);
		}
		for (size_t g = 0; g < 23; g++)
		{
			if (i == 0 && g == 22) //если мы на первой строке, и 22 элементе
			{
				SetColor(ConsoleColor(num_color), ConsoleColor(num_color));
				Sleep(speed); //Задержка, чтобы была анимация
				cout << '+'; //рисуем любой знак, из-за окраски он будет квадратиком
			}
			if (i == 0 && g > 0 && g < 10) //если мы на первой строке, и в диапозоне с 0-го по 10-ый элемент
			{
				SetColor(White, ConsoleColor(num_color));
				Sleep(speed);
				cout << " " << mas[g]; //Пишем пробел, и букву, которая стоит на месте элемента, номер которого равен значению "g"
			}
			else if (i > 0 && i < 11 && g == 0) //если мы находимся с 0-ой по 11-ую строку на 0-м элементе
			{
				SetColor(White, ConsoleColor(num_color));
				if (i < 10) //Если мы находимся на строках не достигающих значения "10"
				{
					Sleep(speed);
					cout << i << ' '; //Пишим цифру указывающая на номер строки, которая будет помогать игроку ориентироваться, куда он стреляет
				}
				else //иначе
				{
					Sleep(speed);
					cout << i; //Пишем цифру без пробелов, так как тут они не будут нужны, ведь цифра которая будет выводиться "10"
				}
			}
			else if (i == 11 || g > 20 && g < 23) //если мы находимся на 11-ой строке, на 21-22-ых элементах
			{
				if (A == 0 && i == 11) //проверка на последней строке, которая нужна, чтобы выводился кубик который не выводится самостоятельно
				{
					Sleep(speed);
					cout << "+";
					A++; //меняем значение переменной благодаря которой было можно реализовать дорисовку нужного кубика
				}
				SetColor(ConsoleColor(num_color), ConsoleColor(num_color));
				Sleep(speed);
				cout << '+';
			}
			else if (i > 0) //если мы находимся на строке номер которой не равен "0" (непосредственно игровое поле)
			{
				Sleep(speed);
				SetColor(White, White);
				cout << '+';
			}
		}
	}
	SetColor(Black, Black); //устанавливаем полностью черный цвет
}
void Paint(char variant[3][30], int T) //меню выбора расстановки 
{
	system("cls"); //очищаем консоль
	for (size_t i = 0; i < 3; i++)
	{
		SetCursor(30, 6 + i);
		for (size_t p = 0; p < 30; p++)
		{
			if (i == T) //проверка на выбранный пункт
			{
				SetColor(Black, White); //выделяем выбранный пункт
			}
			else
			{
				SetColor(White, Black); //убираем выделение выбранного пункта
			}
			cout << variant[i][p]; //выводим пункты в виде тектса
		}
	}
	CreatField(0, 0, 9); //создаём игровое поле занаво
}
void Text(int num)
{
	char variant[12][40] = { "ВРАГ ЦЕЛИТСЯ","ВРАГ ПРОМАЗАЛ!", "ВРАГ ПОПАЛ!", "ВСЕ ТВОИ КОРАБЛИ СОКРУШЕНЫ, УВЫ :(", "ТВОЙ ЧЕРЁД" , "МИМО :(", "ЕСТЬ ПРОБИТИЕ!", "ТЫ ПОБЕДИЛ, ПОЗДРАВЛЯЮ! :)", "+++++++++++++++++++++++++++++++++++++++", "ТЫ ПОПАЛ, ДЕЛАЙ ЕЩЁ ОДИН ХОД!", "КОРАБЛЬ ВРАГА УНИЧТОЖЕН!", "НЕ ХОЧЕШЬ ЛИ ЕЩЁ ОДИН РАУНД?" };
	//список вариантов реплик которые могут вывестись во время игры
	SetCursor(22, 15);
	SetColor(Black, Black);
	for (size_t i = 0; i < 25; i++) //цикл для стирание предыдущего текста
	{
		cout << variant[10][i]; //выводим "+"
		cout << variant[10][i];
	}
	SetCursor(22, 15);
	if (num > 0 && num < 4) //проверяем, если реплики больше относятся к врагу
	{
		SetColor(Red, Black); //Устанавливаем красный цвет текста на черном фоне 
	}
	else //если реплики больше относятся к игроку
	{
		SetColor(Green, Black); //Устанавливаем зеленый цвет текста на черном фоне 
	}
	for (size_t i = 0; i < 30; i++)
	{
		cout << variant[num][i];  //выводим реплики в виде тектса
	}
}