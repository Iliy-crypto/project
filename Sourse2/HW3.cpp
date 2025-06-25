#include <iostream>
#include <iomanip>


using namespace std;

struct STUDENT {
    char FN[50];    
    char LN[50];    
    char GROUP[10]; 
    int SES[5];    
    double AvgSES;  
};

void calculateAvg(STUDENT& student) {
    double sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += student.SES[i];
    }
    student.AvgSES = sum / 5.0;
}

void printS(const STUDENT& student) {
    cout << "Фамилия: " << student.LN << endl;
    cout << "Имя: " << student.FN << endl;
    cout << "Группа: " << student.GROUP << endl;
    cout << "Оценки: ";
    for (int i = 0; i < 5; i++) {
        cout << student.SES[i] << " ";
    }
    cout << endl;
    cout << "Средний балл: " << student.AvgSES << endl;
    cout << "------------------------" << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    STUDENT students[10] = {
        {"Иван", "Иванов", "ГР-101", {5, 4, 5, 4, 5}, 0},
        {"Петр", "Петров", "ГР-102", {4, 4, 3, 5, 4}, 0},
        {"Алексей", "Сидоров", "ГР-101", {5, 5, 5, 5, 5}, 0},
        {"Мария", "Кузнецова", "ГР-103", {3, 4, 4, 3, 4}, 0},
        {"Анна", "Смирнова", "ГР-102", {5, 5, 4, 5, 5}, 0},
        {"Дмитрий", "Васильев", "ГР-101", {4, 3, 4, 3, 4}, 0},
        {"Елена", "Попова", "ГР-103", {5, 4, 5, 4, 5}, 0},
        {"Сергей", "Новиков", "ГР-102", {3, 3, 3, 4, 3}, 0},
        {"Ольга", "Морозова", "ГР-101", {4, 4, 4, 4, 4}, 0},
        {"Николай", "Федоров", "ГР-103", {5, 4, 3, 5, 4}, 0}
    };

    for (int i = 0; i < 10; i++) {
        calculateAvg(students[i]);
    }

    cout << "Список студентов:" << endl;
    cout << "========================" << endl;
    for (int i = 0; i < 10; i++) {
        printS(students[i]);
    }

    return 0;
}