// snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score, fruit2X, fruit2Y;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;

void Logo()
{
    cout << endl << endl;
    cout << R"###(  _________              __            ________                       )###" << endl;
    cout << R"###( /   _____/ ____ _____  |  | __ ____  /  _____/_____    _____   ____  )###" << endl;
    cout << R"###( \_____  \ /    \\__  \ |  |/ // __ \/   \  ___\__  \  /     \_/ __ \ )###" << endl;
    cout << R"###( /        \   |  \/ __ \|    <\  ___/\    \_\  \/ __ \|  Y Y  \  ___/ )###" << endl;
    cout << R"###(/_______  /___|  (____  /__|_ \\___  >\______  (____  /__|_|  /\___  >)###" << endl;
    cout << R"###(        \/     \/     \/     \/    \/        \/     \/      \/     \/ )###" << endl;
    cout << endl;
    system("pause");
}

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    fruit2X = rand() % width;
    fruit2Y = rand() % height;
    score = 0;
}
void Draw()
{
    system("cls"); //system("clear");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else if (i == fruit2Y && j == fruit2X)
                cout << "S";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }


            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl << endl;
    cout << "           W : UP" << endl;
    cout << "A : LEFT   S : DOWN   D : RIGHT" << endl << endl;
    cout << "F = Score + 10" << endl << "S = Score + 30" << endl << endl;
    cout << "Score:" << score << endl;
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    
    if (x >= width) x = 0; 
    else if (x < 0) x = width - 1;

    if (y >= height) y = 0;
    else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }

    if (x == fruit2X && y == fruit2Y)
    {
        score += 30;
        fruit2X = rand() % width;
        fruit2Y = rand() % height;
        nTail++;
    }
}
int main()
{
    Logo();
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(50);
    }
    return 0;
}

