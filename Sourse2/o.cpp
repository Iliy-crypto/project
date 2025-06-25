#include <iostream> 
#include <windows.h>
#include <conio.h>
using namespace std;
enum class Keys
{
    NOSET,

    LEFT = 75,
    RIGHT = 77,
    TOP = 72,
    DOWN = 80,
    ESC = 27,
    SPACE = 32,
    ENTER = 13,

};
void main()
{
    while (true)
    {
        if (_kbhit()) // слушатель нажатия на клавишу
        {
            switch (static_cast<Keys>(_getch())) // ждет нажатия на клавишу
            {
            case Keys::TOP: // вверх
                cout << "Up" << endl;
                break;
            case Keys::DOWN: // вниз
                cout << "Down" << endl;
                break;
            case Keys::LEFT: // влево
                cout << "left" << endl;
                break;
            case Keys::RIGHT: // вправо
                cout << "Right" << endl;
                break;
            case Keys::ESC: // 
                exit(0);
                break;
            }
        }
    }
}