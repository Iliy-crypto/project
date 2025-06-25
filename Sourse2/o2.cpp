#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
using namespace std;

void gotoxy(short x, short y) // аналог борландовской gotoxy
{
    HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD  coord = { x, y };
    SetConsoleCursorPosition(StdOut, coord);
}


void oformlenie()
{
    short x = 18, y = 4;
    gotoxy(x, y);
    cout << "*"; //st-up-left
    while (x != 18 + 40)
    {
        x++;
        gotoxy(x, y);
        cout << "="; //up
    }
    x++;
    gotoxy(x, y);
    cout << "*"; //st-up-right
    while (y != 17)
    {
        y++;
        gotoxy(x, y);
        cout << "\1"; //right
    }
    y++;
    gotoxy(x, y);
    cout << "*"; //st-bot-right
    while (x != 19)
    {
        x--;
        gotoxy(x, y);
        cout << "="; //bottom
    }
    x--;
    gotoxy(x, y);
    cout << "*"; //st-bot-left
    while (y != 5)
    {
        y--;
        gotoxy(x, y);
        cout << "\1"; //left
    }
}

void color(int c)
{
    HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(StdOut, c + 64);
}
void clrscr()
{
    short x = 20, y = 6;
    while (y != 18)
    {
        while (x != 58)
        {
            gotoxy(x, y);
            cout << " ";
            x++;
        }
        y++;
        x = 20;
    }
}

int menu(int i)
{
    setlocale(LC_CTYPE, "");
    system("cls");
    system("color 3F");
    short x = 20, y = 8;
    if (i == 3) y++;
    gotoxy(33, 6);
    cout << "..::MENU::..";
    gotoxy(1, 0);
    cout << "'Esc' - vyiti;   Vybor deistviya: strelkami i klavishei 'Enter';\n Ili je sootvetstvuyushimi ciframi;";
    gotoxy(x, y);
    const char* s[3];
    s[0] = "1 - Avtozapolnenie";
    s[1] = "2 - S klaviatury";
    s[2] = "0 - Exit";
    const char* p[5];
    p[0] = "1 - Sort obmenom";
    p[1] = "2 - Sort vuborkoi";
    p[2] = "3 - Sort vstavkoi";
    p[3] = "4 - Quick sort";
    p[4] = "0 - Exit";
    int m = y;
    int k;
    for (k = 0;k < i;k++)
    {
        if (i == 3)
        {
            cout << s[k];
            m += i;
        }
        else
        {
            cout << p[k];
            m += 2;
        }
        gotoxy(x, m);
    }
    oformlenie();

    gotoxy(x, y);
    //color(11);
    if (i == 3)
        cout << s[0];
    else
        cout << p[0];
    gotoxy(x, y);
    k = 0;
    m = 0;
    char c;
    while (1)
    {
        c = _getch();
        switch (c)
        {
        case 48:
        case 27: return 0;
        case 80:
            if (k + 1 < i)
            {
                gotoxy(x, y);
                //color(15);
                if (i == 3)
                {
                    cout << s[m];
                    y += i;
                }
                else
                {
                    cout << p[m];
                    y += 2;
                }
                k++;
                m = k;
                //color(14);
                gotoxy(x, y);
                if (i == 3)
                    cout << s[k];
                else cout << p[k];
                gotoxy(x, y);
            }
            break;
        case 72:
            if (k >= 1)
            {
                gotoxy(x, y);
                //color(13);
                if (i == 3)
                {
                    cout << s[m];
                    y -= i;
                }
                else
                {
                    cout << p[m];
                    y -= 2;
                }
                k--;
                m = k;
                //color(11);
                gotoxy(x, y);
                if (i == 3)
                    cout << s[k];
                else cout << p[k];
                gotoxy(x, y);
            }
            break;
        case 13:
            //color(15);
            if (i == 3 && k == 2)
                return 0;
            if (i == 5 && k == 4)
                return 0;
            return k + 1;
        case 49:
            color(15);
            return 1;
        case 50:
            color(15);
            return 2;
        case 51:
            color(15);
            return 3;
        case 52:
            color(15);
            return 4;
        }
    }
}
int main(void)
{
    int m = menu(3);
    int n;
    if (m == 0)
        return 0;
    clrscr();
    gotoxy(26, 10);
    cout << "Vvedite razmer massiva: ";
    cin >> n;
    int* mas = new int[n];
    int* rabmas = new int[n];
    if (m == 1)
    {
    }
    else if (m == 2)
    {
        for (int i = 0;i < n;i++)
        {
            gotoxy(35, 12);
            cout << "Mas [" << i << "] = ";
            cin >> mas[i];
            gotoxy(35, 12);
            cout << "                ";
        }
    }
    while (1)
    {
        m = menu(5);
        system("cls");
        for (int i = 0;i < n;i++)
            rabmas[i] = mas[i];
        if (!m) return 0;
        cout << "Массив:";

        cout << "\nOtsortirovannuy massiv:";
    }
    delete[]mas;
    delete[]rabmas;
}