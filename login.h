#pragma once
#pragma pack(1)
#include "header.h"
#include "player.h"
#include "saveFile.h"
#include "NewOrCont.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

bool getSaveFile(savefile &player);
void displayMenu();
void choiceNewOrCont(savefile player);

void printLogin()
{
    system("cls");
    //Doc thong tin tu file
    savefile player,tmp;
    int BackGroundColor = rand() % 15 + 1;

    TextColor(7);
    SetConsoleOutputCP(65001);
    const int heii = 5, widd = 7;
    PlaySound(TEXT("background1.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    char pic[200][200];
    gotoxy(0, 0);
    makePic(5,11,heii,widd,pic,8);
    for(int i = 0; i <= heii * 8; i++)
    {
        for(int j = 0; j <= widd * 19 - (widd - 2) - 6; j++)
        {
            if(j == 0)
                doTab(3);
            if (j > (widd * 19 - (widd - 2) - 24) / 2 )
                TextColor(BackGroundColor);
            else
                TextColor(7);
            cout <<  pic[i][j];
        }
        cout <<  endl;
    }

    gotoxy(0, 23);
    doTab(6);
    TextColor(5);
    cout << "╔════════════════════════════════════════════════════════════════════╗" << endl;
    doTab(6);
    cout << "║              TYPE YOUR ACCOUNT INFORMATION TO LOGIN !!!            ║" << endl;
    doTab(6);
    cout << "╚════════════════════════════════════════════════════════════════════╝" << endl;
    TextColor(7);

    bool sucess = false;

    gotoxy(0, 27);
    doTab(7);
    cout <<  "Username: ";
    gets(player.name);

    gotoxy(0,29);
    doTab(7);
    cout <<  "Password: ";
    char ch;
    string pass = "";
    int x = 1, dem = 0;
    while((ch = _getch()) != 13 && ch != ' ')
    {
        dem++;
        if(ch == 8 && pass.size()>0)
            pass.erase(pass.begin()+pass.size()-1);
        else
        if(ch != 8 )
        pass += ch;
        gotoxy(0, 29);
        doTab(7);
        cout <<  "Password: ";
        for(int i = 0; i < pass.size(); i++)
            cout << '*';
        for(int i = pass.size(); i <= dem; i++)
            cout << ' ';
        cout << endl;
    }
    strcpy(player.password,pass.c_str());

    gotoxy(0,31);
    TextColor(14);
    doTab(7);
    cout << "Press [ S ] to show password, or [ H ] to hide ...";

    TextColor(7);
    while(1)
    {
        if (kbhit()) // Kiểm tra xem có bấm phím kg
        {
            gotoxy(0,29);

            char key = getch(); // Lấy ký tự người dùng vừa bấm

            if (toupper(key)== 'A'|| toupper(key)== 'D' || key == 75 || key == 77) // Di chuyển trái
            {
                ++x;
            }


            if(key == 13 || toupper(key) == 'S'|| toupper(key) == 'H')
            {
                if(x & 1 || toupper(key) == 'S')
                {
                    gotoxy(0, 29);
                    doTab(7);
                    cout <<  "Password: " << pass;
                }
                cout << endl;
                break;
            }

            gotoxy(0, 31);
            doTab(7);
            if(x & 1)
                cout << "Press [ S ] to show password, or [ H ] to hide ...";
            else
                cout << "Press [ S ] to show password, or [ H ] to hide ...";
            cout <<  endl;
        }

    }

    bool existUsername = false;
    // player.level = 1;
    // player.maxScore = 0;

    ifstream fin;
    fin.open("account\\account.dat", ios::binary);
    while(!fin.eof())
    {
        fin.read((char *) &(tmp), sizeof(savefile));
        if(fin.eof())
            break;
        for(int i = 0; i < strlen(tmp.name); i++)
            tmp.name[i] ^= tmp.mask;
        for(int i = 0; i < strlen(tmp.password); i++)
            tmp.password[i] ^= tmp.mask;
        if(strcmp(tmp.name,player.name) == 0 )
        {
            existUsername = true;
            if(strcmp(tmp.password,player.password) == 0)
            {
                TextColor(6);
                doTab(7);
                if(getSaveFile(player))
                    cout << "Loaded savefile !!!" << endl;
                else
                {
                    for(int i = 0; i < 5; i++)
                    {
                        player.record[i].points = tmp.record[i].points;
                        player.record[i].date.dd = tmp.record[i].date.dd;
                        player.record[i].date.mm = tmp.record[i].date.mm;
                        player.record[i].date.yy = tmp.record[i].date.yy;
                        player.state[i].q = tmp.state[i].q;
                        player.state[i].q_ = tmp.state[i].q_;
                        player.state[i].p = tmp.state[i].p;
                        player.state[i].p_ = tmp.state[i].p_;
                        for(int j = 0; j < player.state[i].q * player.state[i].p; j++)
                            player.state[i].board[j] = tmp.state[i].board[j];

                        // for(int j = 0; j < player.state[i].q * player.state[i].p; j++)
                        //     player.state[i].file_background[j] = tmp.state[i].file_background[j];
                    }
                }
                cout << endl;
                cout << endl;
                cout << endl;
                PlaySound(TEXT("Hint.wav"), NULL, SND_FILENAME | SND_ASYNC);
                doTab(7);
                cout << "Login successfully !!!" << endl;
                doTab(7);
                cout << "Press any key to continue !!!" << endl;
                TextColor(7);

                ch = _getch();
                choiceNewOrCont(player);
                fin.close();
                return;
            }
        }
    }
    fin.close();
    if(!sucess)
    {
        TextColor(4);
        gotoxy(0, 33);
        doTab(7);
        PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
        if(existUsername)
            cout << "Your password is wrong !!!" << endl;
        else
            cout << "Your username is not exist !!!" << endl;
        TextColor(6);
        cout << endl;
        doTab(7);
        cout << "Press B to back to Menu or others key to login again !!!" << endl;
        TextColor(7);
        ch = _getch();
        if(toupper(ch) == 'B')
            displayMenu();
        else
        printLogin();
    }
}
