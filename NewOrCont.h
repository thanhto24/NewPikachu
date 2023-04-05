#pragma once
#include "header.h"
#include "player.h"
#include "saveFile.h"
#include "menu.h"
#include "Continue.h"

void displayMenu();

void choiceLevel(savefile player);
void doContinue(savefile player);

bool canCont(savefile player)
{
    for (int i = 0; i < 5; i++)
        if (player.state[i].p_ != -1)
            return true;
    return false;
}

void choiceNewOrCont(savefile player)
{
    system("cls");
    PlaySound(TEXT("background2.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    SetConsoleOutputCP(65001);
    const int heii = 5, widd = 7;
    // char pic[heii hei - (heii)+1][widd * wid - (widd - 2) - 7+1];
    char pic[200][200];
    gotoxy(0, 3);
    makePic(5,11,heii,widd,pic,4);
    for(int i = 0; i <= heii * 6 + 4; i++)
    {
        for(int j = 0; j <= widd * 20 + 10; j++)
        {
            if(j == 0)
                doTab(2);
            if (j % 2 == 0)
                TextColor(13);
            else
                TextColor(7);
            cout <<  pic[i][j];
        }
        cout <<  endl;
    }
    TextColor(7);

    gotoxy(0, 30);
    doTab(6);
    TextColor(3);
    cout << "╔════════════════════════════════════════════════════════════════════╗" << endl;
    doTab(6);
    cout << "║               HELLO POKEMON-ERS USING THIS PROGRAM !!!             ║" << endl;
    doTab(6);
    cout << "╚════════════════════════════════════════════════════════════════════╝" << endl;
    TextColor(7);

    string bar[3];
    bar[0] = "  [ NEW GAME ]  ";
    bar[1] = "  [ CONTINUE ]  ";
    bar[2] = " [ BACK TO MENU ] ";

    int x = 0;

    bar[x][0] = '>';
    bar[x][bar[x].size() - 1] = '<';

    gotoxy(0, 34);
    doTab(5);
    for (int i = 0; i < 3; i++)
    {
        if (i == 1 && !canCont(player))
            TextColor(4);
        cout << bar[i];
        TextColor(7);
        doTab(2);
    }

    bar[x][0] = ' ';
    bar[x][bar[x].size() - 1] = ' ';

    cout << endl;

    while (1)
    {

        if (kbhit()) // Kiểm tra xem có bấm phím kg
        {
            gotoxy(0, 34);

            char key = getch(); // Lấy ký tự người dùng vừa bấm

            if (toupper(key) == 'A' || key == 75) // Di chuyển trái
            {
                x--;
                if (x < 0)
                    x = 2;
                PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            if (toupper(key) == 'D' || key == 77) // Di chuyển phải
            {
                x++;
                if (x > 2)
                    x = 0;
                PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }

            if (key == 13)
            {
                if (!x)
                {
                    PlaySound(TEXT("match.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    choiceLevel(player);
                }
                if (x & 1)
                {
                    if (canCont(player))
                    {
                        PlaySound(TEXT("match.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        return void(doContinue(player));
                    }
                    PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    continue;
                }
                if (x == 2)
                {
                    PlaySound(TEXT("match.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    displayMenu();
                }
                return;
            }
            bar[x][0] = '>';
            bar[x][bar[x].size() - 1] = '<';

            gotoxy(0, 34);
            doTab(5);
            for (int i = 0; i < 3; i++)
            {
                if (i == 1 && !canCont(player))
                    TextColor(4);
                cout << bar[i];
                TextColor(7);
                doTab(2);
            }
            bar[x][0] = ' ';
            bar[x][bar[x].size() - 1] = ' ';
            cout << endl;
        }
    }
}
