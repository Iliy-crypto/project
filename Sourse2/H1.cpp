#include <string.h>
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <stdlib.h>

using namespace std;

int main() {
    // Установка русской локализации для корректного отображения кириллицы
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const int MAX_SIZE = 100; // Максимальный размер массива
    char str[MAX_SIZE] = "";  // Исходная строка
    char newStr[MAX_SIZE] = ""; // Для хранения отрезка строки
    char tempStr[MAX_SIZE] = ""; // Временная строка для операций
    char symbol; // Символ для поиска
    int m, n; // Границы для операций

    // Задание 1: Проверка занятых и свободных элементов массива
    cout << "Задание 1:\nВведите строку: ";
    cin.getline(str, MAX_SIZE);

    int length = strlen(str);
    cout << "Занято элементов: " << length << endl;
    cout << "Свободно элементов: " << MAX_SIZE - length - 1 << endl; // -1 для нуль-терминатора

    // Задание 2: Отображение и запись отрезка строки
    cout << "\nЗадание 2:\nВведите m и n (начальный и конечный индексы): ";
    cin >> m >> n;
    cin.ignore(); // Очистка буфера после ввода чисел

    // Проверка корректности введенных границ
    if (m < 1 || n > length || m > n) {
        cout << "Ошибка: неверные границы отрезка!\n";
    }
    else {
        // Копирование отрезка строки
        strncpy(newStr, str + m - 1, n - m + 1);
        newStr[n - m + 1] = '\0'; // Добавление нуль-терминатора

        cout << "Отрезок строки: " << newStr << endl;
    }

    // Задание 3: Удаление символов с m по n
    cout << "\nЗадание 3:\nВведите m и n для удаления: ";
    cin >> m >> n;
    cin.ignore();

    if (m < 1 || n > length || m > n) {
        cout << "Ошибка: неверные границы для удаления!\n";
    }
    else {
        // Копирование части до m
        strncpy(tempStr, str, m - 1);
        tempStr[m - 1] = '\0';

        // Добавление части после n
        strcat(tempStr, str + n);

        // Копирование результата обратно в исходную строку
        strcpy(str, tempStr);

        cout << "Строка после удаления: " << str << endl;
    }

    // Задание 4: Поиск всех совпадений символа
    cout << "\nЗадание 4:\nВведите строку: ";
    cin.getline(tempStr, MAX_SIZE);
    cout << "Введите символ для поиска: ";
    cin >> symbol;
    cin.ignore();

    cout << "Позиции символа '" << symbol << "': ";
    bool found = false;
    for (int i = 0; i < strlen(tempStr); i++) {
        if (tempStr[i] == symbol) {
            cout << i + 1 << " ";
            found = true;
        }
    }
    if (!found) cout << "совпадений не найдено";
    cout << endl;

    // Задание 5: Поиск последнего совпадения символа
    cout << "\nЗадание 5:\nВведите строку: ";
    cin.getline(tempStr, MAX_SIZE);
    cout << "Введите символ для поиска: ";
    cin >> symbol;

    int lastPos = -1;
    for (int i = 0; i < strlen(tempStr); i++) {
        if (tempStr[i] == symbol) {
            lastPos = i + 1;
        }
    }

    if (lastPos == -1) {
        cout << "Символ не найден\n";
    }
    else {
        cout << "Последнее вхождение символа на позиции: " << lastPos << endl;
    }

    return 0;
}