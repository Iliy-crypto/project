#include <string.h>
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <stdlib.h>
#include <MMSystem.h>
#pragma comment (lib, "winmm")
#define _CRT_SECURE_NO_WARNINGS


using namespace std;



int main() {
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    PlaySound(TEXT("Start.wav"), NULL, SND_ASYNC | SND_LOOP);







}