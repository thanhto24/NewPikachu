#pragma once
#include "header.h"
#include "login.h"
#include "signup.h"
#include "makePicture.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void doTab(int cnt);

void makePic(int hei, int wid, int n, int m, char pic[200][200], int num);
void menuMove(int &choice);
void printHelp();
void printHighScore();
void printCredit();

void displayMenu()
{
    system("cls");
    const int heii = 5, widd = 7;
    int BackGroundColor = rand() % 15 + 1;
    char pic[200][200];
    PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    gotoxy(0,5);
    makePic(5,11,heii,widd,pic,0);
    TextColor(10);
    for(int i = 0; i <= heii * 5 - (heii); i++)
    {
        for(int j = 0; j <= widd * 15 - (widd - 2) - 6; j++)
        {
            if(j == 0)
                doTab(4);
            if (j % 2 == 0)
                TextColor(BackGroundColor);
            else
                TextColor(7);
            cout <<  pic[i][j];
        }
        cout <<  endl;
    }

    TextColor(14);
    cout <<  endl;
    int choice = 0;
    menuMove(choice);
    system("cls");
    if(choice == 0)
        printLogin();
    if(choice == 1)
        printSignUp();
    if(choice == 2)
        printHelp();
    if(choice == 3)
        printCredit();
    if(choice == 4)
        printHighScore();
    if(choice == 5)
    {
        SetConsoleOutputCP(65001);
        cout << R"(
╔═══════════════════╗
║ EXIT SUCCESSFULLY ║
╚═══════════════════╝ )";
        exit(0);
    }
}

void menuMove(int &x)
{
    string bar[6];

    bar[0] = "  [ LOGIN ]  ";
    bar[1] = "  [ SIGN UP ]  ";
    bar[2] = "  [ HELP ]  ";
    bar[3] = "  [ CREDIT ]  ";
    bar[4] = "  [ TOP HIGH SCORE ]  ";
    bar[5] = "  [ EXIT ]  ";


    bar[x][0] = '>';
    bar[x][bar[x].size() - 1] = '<';

    cout << endl;
    doTab(1);
    for(int i = 0; i < 6; i++)
    {
        cout << bar[i];
        doTab(2);
    }

    bar[x][0] = ' ';
    bar[x][bar[x].size() - 1] = ' ';

    cout <<  endl;

    while(1)
    {

        if (kbhit()) // Kiểm tra xem có bấm phím kg
        {
            gotoxy(0,27);

            char key = getch(); // Lấy ký tự người dùng vừa bấm

            if (toupper(key)== 'A' || key == 75) // Di chuyển trái
            {
                x--;
                if (x < 0)
                    x = 5;
                if (x == 0)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                else if (x == 1)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                else if (x == 2)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                else if (x == 3)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                if (x == 4)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                if (x == 5)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }

            if (toupper(key)== 'D' || key == 77) // Di chuyển phải
            {
                x++;
                if (x > 5)
                    x = 0;
                if (x == 0)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                else if (x == 1)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                else if (x == 2)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                else if (x == 3)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                if (x == 4)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                if (x == 5)
                    PlaySound(TEXT("enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }

            if(key == 13)
            {
                return void(system("cls"));
            }

        bar[x][0] = '>';
        bar[x][bar[x].size()-1] = '<';
        cout << endl;
        doTab(1);
        for(int i = 0; i < 6; i++)
        {
            cout <<  bar[i];
            doTab(2);
        }
        bar[x][0] = ' ';
        bar[x][bar[x].size()-1] = ' ';
        cout <<  endl;
        }
    }
}

void printHelp()
{
    system("cls");
    SetConsoleOutputCP(65001);
    const int heii = 5, widd = 7;
    int BackGroundColor = rand() % 15 + 1;

    char pic[200][200];
    gotoxy(0,0);
    makePic(5,11,heii,widd,pic,5);
    PlaySound(TEXT("background1.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    TextColor(10);
    for(int i = 0; i <= heii * 9; i++)
    {
        for(int j = 0; j <= widd * 21; j++)
        {
            if(j == 0)
                doTab(0);
            if (j % 2 == 0)
                TextColor(BackGroundColor);
            else
                TextColor(7);
            cout <<  pic[i][j];
        }
        cout <<  endl;
    }
    gotoxy(0, 3);
    TextColor(14);
    doTab(4);
    cout <<  "   ╔════════════════════════════════════════════════════════════════════╗" << endl;
    doTab(4);
    cout <<  "   ║                          ~~ TUTORIAL ~~                            ║" << endl;
    doTab(4);
    cout <<  "   ╠════════════════════════════════════════════════════════════════════╣" << endl;
    doTab(4);
    cout <<  "   ║     I/ HOW TO PLAY ?                                               ║" << endl;
    doTab(4);
    cout <<  "   ║ 1. Press A/S/D/W or arrows to move LEFT/DOWN/RIGHT/LEFT.           ║" << endl;
    doTab(4);
    cout <<  "   ║ 2. Press Enter to select the cell.                                 ║" << endl;
    doTab(4);
    cout <<  "   ║ 3. Press Z to undo, Shift + '!' for hint and R to swap all cells.  ║" << endl;
    doTab(4);
    cout <<  "   ║ 4. Remember that you must finish each mode sequentially.           ║" << endl;
    doTab(4);
    cout <<  "   ║ 5. The less time you finish this game, the more high score you get.║" << endl;
    doTab(4);
    cout <<  "   ╠════════════════════════════════════════════════════════════════════╣" << endl;
    TextColor(13);
    doTab(4);
    cout <<  "   ║     II/ HOW TO LOGIN ?                                             ║" << endl;
    doTab(4);
    cout <<  "   ║         You need to have an account to login.                      ║" << endl;
    doTab(4);
    cout <<  "   ╠════════════════════════════════════════════════════════════════════╣" << endl;

    TextColor(10);
    doTab(4);
    cout <<  "   ║     III/ HOW TO SIGN UP ?                                          ║" << endl;
    doTab(4);
    cout <<  "   ║         You need to offer your user's name,                        ║" << endl;
    doTab(4);
    cout <<  "   ║         which never be used, and a password strong enough !!!      ║" << endl;
    doTab(4);
    cout <<  "   ╚════════════════════════════════════════════════════════════════════╝" << endl;

    TextColor(7);
    cout << endl;
    doTab(4);
    cout <<  "   If you do not have an account, press [ Y ] to sign up, or [ N ] to login: " << endl;

    string pick[2];
    pick[0] = "[ Y ]";
    pick[1] = "[ N ]";

    int x = 0;

    pick[x][1] = pick[x][3] = 176;

    pick[x][1] = pick[x][3] = ' ';

    while(1)
    {
        if (kbhit()) // Kiểm tra xem có bấm phím kg
        {
            gotoxy(0,17);

            char key = getch(); // Lấy ký tự người dùng vừa bấm

            if (toupper(key)== 'A'|| toupper(key)== 'D'|| key==75 || key==77) // Di chuyển trái
            {
                ++x;
            }


            if(key == 13 || toupper(key) == 'Y' || toupper(key) == 'N' || toupper(key) == 'y' || toupper(key) == 'n')
            {
                if(x & 1 || key=='Y' || toupper(key) == 'y')
                    printSignUp();
                else
                    printLogin();
                return;
            }

            if(x & 1)
                cout <<"   If you don not have an account, press [ Y ] to sign up, or [ N ] to login";
            else
                cout <<"   If you don not have an account, press [ Y ] to sign up, or [ N ] to login";
            cout <<  endl;
        }
    }
}

bool cmp(savefile a, savefile b)
{
    for (int i = 5 - 1; i >= 0; i--)
        if (a.record[i].points >=0 || b.record[i].points >= 0)
            return a.record[i].points > b.record[i].points;
}

void printHighScore()
{
    system("cls");

    savefile tmp;
    vector<savefile> topPlayer;

    ifstream fin;
    fin.open("account\\account.dat", ios::binary);
    while(!fin.eof())
    {
        fin.read((char *) &(tmp), sizeof(savefile));
        if(fin.eof())
            break;
        topPlayer.push_back(tmp);
        if (topPlayer.size() == 5)
            break;
    }
    fin.close();

    sort(topPlayer.begin(),topPlayer.end(),cmp);

    const int heii = 5, widd = 7;
    // char pic[heii hei - (heii)+1][widd * wid - (widd - 2) - 7+1];
    char pic[200][200];
    gotoxy(0,2);
    makePic(5,11,heii,widd,pic,6);
    PlaySound(TEXT("background1.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    TextColor(10);
    for(int i = 0; i <= heii * 2 - (heii) + 2; i++)
    {
        for(int j = 0; j <= widd * 15 - (widd - 2) - 6; j++)
        {
            if(j == 0)
            {
                doTab(3);
                cout << "        ";
            }
            if (j % 2 == 0)
                TextColor(3);
            else
                TextColor(7);
            cout <<  pic[i][j];
        }
        cout <<  endl;
    }

    TextColor(10);
    for (int i = 0; i < topPlayer.size(); i++)
    {
        doTab(6);
        for(int k = 0; k < strlen(topPlayer[i].name); k++)
            topPlayer[i].name[k] ^= topPlayer[i].mask;

        for (int k = 5 - 1; k >= 0; k--)
        {
            if (topPlayer[i].record[k].points > 0)
            {
                cout <<topPlayer[i].name;

                for (int j = 0; j < 30 - strlen(topPlayer[i].name); j++)
                    cout << '_';
                cout <<topPlayer[i].record[k].points;

                int dem = 0;
                if (!topPlayer[i].record[k].points)
                    dem++;

                while (topPlayer[i].record[k].points > 0)
                {
                    topPlayer[i].record[k].points /= 10;
                    dem++;
                }

                for (int j = 0; j < 6 - dem; j++)
                    cout << ' ';
                cout <<" ( Level: " << k + 1 << ", at " <<  setw (2) << topPlayer[i].record[k].date.dd << setfill('0') << " / " << setw(2) << topPlayer[i].record[k].date.mm << setfill('0') << " / " << setw(4) << topPlayer[i].record[k].date.yy << setfill('0') <<" )\n\n";

                k = -1; // Break khoi vong for k
            }
        }
        cout << endl;
    }

    cout << endl;
    TextColor(6);
    doTab(8);
    cout <<  "Press any key to back to menu !!!\n";
    TextColor(7);

    char ch;
    ch = _getch();
    displayMenu();
}

void printCredit()
{
    system("cls");
    SetConsoleOutputCP(65001);
    const int heii = 5, widd = 7;
    int BackGroundColor = rand() % 15 + 1;

    char pic[200][200];
    gotoxy(0,0);
    makePic(5,11,heii,widd,pic,5);
    PlaySound(TEXT("background1.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    TextColor(10);
    for(int i = 0; i <= heii * 9; i++)
    {
        for(int j = 0; j <= widd * 21; j++)
        {
            if(j == 0)
                doTab(0);
            if (j % 2 == 0)
                TextColor(BackGroundColor);
            else
                TextColor(7);
            cout <<  pic[i][j];
        }
        cout <<  endl;
    }
    gotoxy(0, 3);
    TextColor(13);
    doTab(4);
    cout << "   ╔═══════════════════════════════════════════════════════════════════╗" << endl;
    doTab(4);
    cout << "   ║                         ~~ CREDIT ~~                              ║" << endl;
    doTab(4);
    cout << "   ║              UNIVERSITY OF SCIENCE IN HOCHIMINH CITY              ║" << endl;
    TextColor(7);
    doTab(4);
    cout << "   ╠═══════════════════════════════════════════════════════════════════╣" << endl;
    doTab(4);
    cout << "   ║ * This program is coded by students from HCMUS:                   ║" << endl;
    doTab(4);
    cout << "   ║      Dev 1: To Quoc Thanh.                                        ║" << endl;
    doTab(4);
    cout << "   ║      Dev 2: Le Phuoc Phat.                                        ║" << endl;
    doTab(4);
    cout << "   ╠═══════════════════════════════════════════════════════════════════╣" << endl;
    TextColor(10);
    doTab(4);
    cout << "   ║ * Thanks all supporting and helping from our teachers:            ║" << endl;
    doTab(4);
    cout << "   ║      Mr.Nguyen Thanh Phuong.                                      ║" << endl;
    doTab(4);
    cout << "   ║      Mr.Bui Huy Thong.                                            ║" << endl;
    doTab(4);
    cout << "   ║      Ms.Nguyen Ngoc Thao.                                         ║" << endl;
    doTab(4);
    cout << "   ╠═══════════════════════════════════════════════════════════════════╣" << endl;
    TextColor(14);
    doTab(4);
    cout << "   ║ PLEASE DONOT COPY OR USE OUR PROGRAM FOR ANY PURPOSES !!!         ║" << endl;
    doTab(4);
    cout << "   ║ THANKS ALL FOR PLAYING !!! HAVE A GOOD TIME !!!                   ║" << endl;
    doTab(4);
    cout << "   ╚═══════════════════════════════════════════════════════════════════╝" << endl;

    TextColor(6);
    cout << endl;
    doTab(6);
    cout << "     Press any key to back to menu!" << endl;
    TextColor(7);

    char ch;
    ch = _getch();
    displayMenu();
}
