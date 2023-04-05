#pragma once
#include "header.h"
#include "init.h"
#include "makePicture.h"
#include "display.h"
#include "boardSetting.h"
#include "logicGame.h"
#include "checkMove.h"
#include "slide.h"
#include "play.h"
#include "player.h"
#include "menu.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void makeLevel(int hei, int wid, int n, int m, int choosenLevel, savefile &player, bool is_cont)
{
    char C[200][200], a[200][200];
    bool ate[200][200];
    bool movingOn[200][200], selected[200][200];
    char view[200][200], pic[200][200], cpy[200][200];

    if (is_cont)
    {
        n = player.state[choosenLevel - 1].p;
        m = player.state[choosenLevel - 1].q;
    }
    else
    {
        player.state[choosenLevel - 1].p = n;
        player.state[choosenLevel - 1].q = m;
        updateFile(player);
    }

    system("cls");
    init(hei, wid, n, m, C, view, ate, choosenLevel, player, is_cont);
    // if (player.state[choosenLevel - 1].file_background[0])// bug eo biet sua
        makePic(hei, wid, n, m, pic, choosenLevel);
    // else
    // {
    //     int dem = 0;
    //     for (int i = 0; i < n; i++)
    //         for (int j = 0; j < m; j++)
    //             if (dem < 100)
    //             {
    //                 pic[i][j] = player.state[choosenLevel - 1].file_background[dem];
    //                 dem++;
    //             }
    //             else
    //                 pic[i][j] = ' ';
    // }
    process(hei, wid, n, m, C, view, pic, ate, movingOn, selected, cpy, player, choosenLevel, is_cont);
}

void choiceLevel(savefile player)
{
    system("cls");

    SetConsoleOutputCP(65001);
    const int heii = 5, widd = 7;
    // char pic[heii hei - (heii)+1][widd * wid - (widd - 2) - 7+1];
    char pic[200][200];
    gotoxy(0, 3);
    makePic(5,11,heii,widd,pic,9);
    int backgroundColor = rand() % 15 + 1;
    PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    for(int i = 0; i <= heii * 5 - (heii); i++)
    {
        for(int j = 0; j <= widd * 20 - (widd - 2) - 6; j++)
        {
            if(j == 0)
                doTab(1);
            if (j % 2 == 0)
                TextColor(backgroundColor);
            else
                TextColor(7);
            cout << pic[i][j];
        }
        TextColor(7);
        cout << endl;
    }

    gotoxy(0, 13);
    cout << endl;
    doTab(5);
    TextColor(5);
    cout << "╔════════════════════════════════════════════════════════════════════╗" << endl;
    doTab(5);
    cout << "║            PLEASE CHOOSE YOUR OPTIONS TO PLAY THE GAME !!!         ║" << endl;
    doTab(5);
    cout << "╚════════════════════════════════════════════════════════════════════╝" << endl;

    string levelName[8];

    levelName[0] = "    ╔════════════════════╗    ";
    levelName[1] = "    ║      EASY MODE     ║    ";
    levelName[2] = "    ║     MEDIUM MODE    ║    ";
    levelName[3] = "    ║      HARD MODE     ║    ";
    levelName[4] = "    ║  EXTREME HARD MODE ║    ";
    levelName[5] = "    ║     CUSTOM MODE    ║    ";
    levelName[6] = "    ║    BACK TO MENU    ║    ";
    levelName[7] = "    ╚════════════════════╝    ";

    int x = 1;

    levelName[x][0] = '>';
    levelName[x][levelName[x].size() - 1] = '<';

    gotoxy(0, 19);
    for (int i = 0; i < 8; i++)
    {
        if (i == 0)
            TextColor(7);
        else if (i == 5)
            TextColor(7);
        else if(i == 6)
            TextColor(6);
        else if (i == 7)
            TextColor(7);
        else if (player.record[i - 1].points == -1)
            TextColor(4);
        doTab(7);
        cout << "    " << levelName[i] << endl;
        TextColor(7);
    }
    levelName[x][0] = ' ';
    levelName[x][levelName[x].size() - 1] = ' ';
    cout << endl;

    while (1)
    {

        if (kbhit()) // Kiểm tra xem có bấm phím kg
        {
            gotoxy(0, 20);

            char key = getch(); // Lấy ký tự người dùng vừa bấm

            if (toupper(key) == 'W' || key == 72) // Di chuyển trái
            {
                x--;
                if (x < 1)
                    x = 6;
                if (x == 1)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                else if (x == 2)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                else if (x == 3)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                else if (x == 4)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                else if (x == 5)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                else if (x == 6)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            if (toupper(key) == 'S' || key == 80) // Di chuyển phải
            {
                x++;
                if (x > 6)
                    x = 1;
                if (x == 1)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                else if (x == 2)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                else if (x == 3)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                else if (x == 4)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                else if (x == 5)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                else if (x == 6)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }

            if (key == 13)
            {
                if (x == 6)
                {
                    system("cls");
                    displayMenu();
                    exit(0);
                }
                if (x == 5)
                    while (true)
                    {
                        system("cls");
                        cout << "Input heigth and width: ";
                        int h, w;
                        cin >> h >> w;
                        if (h <= 0 || w <= 0)
                            cout << "Data error, please input heigth and width greater than 0\n";
                        else
                        {
                            if (h & 1 || w & 1)
                            {
                                cout << "Data error, input must be even numbers\nSo we change " << h << " x " << w << " to ";
                                if (h & 1)
                                    h++;
                                h = min(h, 20);
                                if (w & 1)
                                    w++;
                                w = min(w, 20);
                                TextColor(4);
                                cout << h;
                                TextColor(7);
                                cout << " x ";
                                TextColor(4);
                                cout << w << endl;
                                TextColor(7);
                            }

                            TextColor(6);
                            cout <<  "Custom game successfully!";
                            cout << "\nPress any key to continue\n";
                            TextColor(7);

                            char ch;
                            ch = _getch();
                            if(h > 8 || w > 16)
                                makeLevel((40 / h) / 2 * 2 + 1, (160 / w ) / 2 * 2 + 1, h, w, x, player, 0);
                            else
                                makeLevel(5, 11, h, w, x, player, 0);
                            return;
                        }
                        Sleep(3000);
                    }

                if (player.record[x - 1].points == -1)
                    continue;

                if (x == 1)
                    // makeLevel(5, 11, 2, 2, x + 1, player); // Turn on to cheat
                    makeLevel(5, 11, 4, 4, x, player, 0);
                if (x == 2)
                    // makeLevel(5, 11, 2, 2, x + 1, player);
                    makeLevel(5, 11, 6, 8, x, player, 0);
                if (x == 3)
                    // makeLevel(5, 11, 2, 2, x + 1, player);
                    makeLevel(5, 11, 10, 14, x, player, 0);
                if (x == 4)
                    // makeLevel(5, 11, 2, 2, x + 1, player);
                    makeLevel(3, 9, 20, 20, x, player, 0);

                return;
            }

            gotoxy(0, 19);
            levelName[x][0] = '>';
            levelName[x][levelName[x].size() - 1] = '<';
            for (int i = 0; i < 8; i++)
            {
                if (i == 0)
                    TextColor(7);
                else if (i == 5)
                    TextColor(7);
                else if(i == 6)
                    TextColor(6);
                else if (i == 7)
                    TextColor(7);
                else if (player.record[i - 1].points == -1)
                    TextColor(4);
                doTab(7);
                cout << "    " << levelName[i] << endl;
                TextColor(7);
            }
            levelName[x][0] = ' ';
            levelName[x][levelName[x].size() - 1] = ' ';
            cout << endl;
        }
    }
}
