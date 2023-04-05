#pragma once
#include "header.h"
#include "player.h"
#include "menu.h"
#include "level.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void unSelect(int n, int m, bool ate[200][200], bool selected[200][200])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (selected[i][j] && !ate[i + 1][j + 1])
                selected[i][j] = false;
}

void calcTime(const int TIME, int &timeLeft, int &prevTime, int m1, int s1, int m2, int s2, int &Point)
{
    timeLeft = TIME - (m2 - m1) * 60 - (s2 - s1);
    if (timeLeft >= 0)
    {
        if (prevTime != timeLeft)
        {
            gotoxy(0, 2);
            TextColor(7);

            if (timeLeft <= 15)
            {
                TextColor(4);
                PlaySound(TEXT("timeup.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }

            cout << "Time left: ";
            cout << setw(2) << setfill('0') << timeLeft / 60 << " : " << setw(2) << setfill('0') << timeLeft % 60;
            TextColor(7);

            doTab(1);

            if(timeLeft&1)
                Point--; // 2 giay mat 1 diem, de neu dung help hoac swap kho bi phat hien
            cout << "Your Point: ";
            TextColor(3);
            cout << Point << "   " << endl;
            TextColor(7);
        }
        prevTime = timeLeft;
    }
    else
        timeLeft = -1;
}

void printInfo(savefile player, int Swap, int Hint)
{
    gotoxy(0,1);
    cout << "Hello player: ";
    TextColor(1);
    cout << player.name;
    TextColor(7);

    doTab(1);
    cout << "Swap left: ";
    TextColor(6);
    cout << Swap;
    TextColor(7);

    doTab(1);
    cout << "Hint left: ";
    TextColor(2);
    cout << Hint;
    TextColor(7);

    doTab(3);
    TextColor(4);
    cout << "Double press Backspace button to Back to menu !!!";

}

void move(int hei, int wid, int n, int m, int &y, int &x, bool &stop, char C[200][200], char view[200][200], char pic[200][200], bool ate[200][200], bool movingOn[200][200], bool selected[200][200], char cpy[200][200], int &Swap, int &Hint, const int TIME, int &timeLeft, const int m1, const int s1, int &Point, const int choosenLevel){
    int X[2], Y[2], cnt = 0;
    bool isSlide = true;
    int prevTime = timeLeft;

    // select va  movingOn chay tu 0 den n - 1
    while (true)
    {
        int m2, s2;
        time_t now = time('\0');
        tm *t = localtime(&now);
        m2 = t->tm_min;
        s2 = t->tm_sec;

        calcTime(TIME, timeLeft, prevTime, m1, s1, m2, s2, Point);

        if (timeLeft == -1)
            return;

        if (kbhit()) // Kiểm tra xem có bấm phím kg
        {
            char key = getch(), prevKey; // Lấy ký tự người dùng vừa bấm

            if(key == prevKey && prevKey == 8)
            {
                stop = true;
                return;                
            }

            if (toupper(key) == 'A' || key == 75) // Di chuyển trái
            {
                x--;
                if (x < 0)
                    x = m - 1;
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            if (toupper(key) == 'D' || key == 77) // Di chuyển phải
            {
                x++;
                if (x >= m)
                    x = 0;
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            if (toupper(key) == 'W' || key == 72) // Di chuyển lên
            {
                y--;
                if (y < 0)
                    y = n - 1;
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            if (toupper(key) == 'S' || key == 80) // Di chuyển xuống
            {
                y++;
                if (y >= n)
                    y = 0;
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }

            if (toupper(key) == 'R')
            {
                Swap--;
                if(Swap<0)
                {
                    Swap = 0;
                    continue;
                }
                PlaySound(TEXT("swap.wav"), NULL, SND_FILENAME | SND_ASYNC);
                Point -= 10;
                unSelect(n, m, ate, selected); // Neu player da chon 1 o ma bam R thi se bug, nen neu bam R thi thao select het
                refreshArray(hei, wid, n, m, C, view, ate);
                printBoard(hei, wid, n, m, 2, view, pic, movingOn, selected, cpy);
                Sleep(300);

                movingOn[y][x] = true;
                printBoard(hei, wid, n, m, 0, view, pic, movingOn, selected, cpy);
                movingOn[y][x] = false;
                
                return;
            }

            // Nhấn z để tháo select

            if (toupper(key) == 'Z')
            {
                unSelect(n, m, ate, selected);
                PlaySound(TEXT("error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                cnt = 0;
            }

            if (key == '!')
            {
                Hint--;
                if(Hint < 0)
                {
                    Hint = 0;
                    continue;
                }
                PlaySound(TEXT("Hint.wav"), NULL, SND_FILENAME | SND_ASYNC);
                Point -= 10;
                unSelect(n, m, ate, selected);
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= m; j++)
                        for (int k = 1; k <= n; k++)
                            for (int l = 1; l <= m; l++)
                                if (!ate[i][j] && !ate[k][l]) // Nếu 2 ô chưa đi
                                    if (finalCheck(hei,wid,i, j, k, l, n, m, 0, C, view, pic, ate, movingOn, selected, cpy))
                                    {
                                        setHint(hei, wid, i, j, view);
                                        setHint(hei, wid, k, l, view);
                                        printBoard(hei, wid,n, m, 0, view, pic, movingOn, selected, cpy);
                                        Sleep(300);

                                        movingOn[y][x] = true;
                                        printBoard(hei, wid, n, m, 0, view, pic, movingOn, selected, cpy);
                                        movingOn[y][x] = false;

                                        return;
                                    }
            }

            if (key != 13)
            {
                memset(movingOn, false, sizeof(movingOn));
                movingOn[y][x] = true;
                printBoard(hei, wid, n, m, 0, view, pic, movingOn, selected, cpy);
                movingOn[y][x] = false; // Neu khong gan lai thi no se movingOn tat ca cac o da di qua
            }

            // Nhấn enter để chọn ô y x
            if (key == 13)
            {
                if (ate[y + 1][x + 1])
                    continue;
                PlaySound(TEXT("error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                selected[y][x] = true;
                Y[cnt] = y;
                X[cnt] = x;
                if (cnt == 1)
                {
                    int y1 = Y[1 - 1] + 1, y2 = Y[2 - 1] + 1, x1 = X[1 - 1] + 1, x2 = X[2 - 1] + 1;

                    if (x1 > x2)
                    {
                        swap(x1, x2);
                        swap(y1, y2);
                    }

                    if (finalCheck(hei,wid,y1, x1, y2, x2, n, m, 1, C, view, pic, ate, movingOn, selected, cpy))
                    {
                        if (isSlide)
                        {
                            PlaySound(TEXT("match.wav"), NULL, SND_FILENAME | SND_ASYNC);
                            int tmp = min(4,choosenLevel);
                            if (tmp == 1)
                                doSlideUp(hei, wid, y1, x1, y2, x2, n, m, C, view, ate);
                            if (tmp == 2)
                                doSlideDown(hei, wid, y1, x1, y2, x2, n, m, C, view, ate);
                            if (tmp == 3)
                                doSlideRight(hei, wid, y1, x1, y2, x2, n, m, C, view, ate);
                            if (tmp == 4)
                                doSlideLeft(hei, wid, y1, x1, y2, x2, n, m, C, view, ate);
                        }
                        else
                        {
                            PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
                            setAte(hei, wid, y1, x1, C, view, ate);
                            setAte(hei, wid, y2, x2, C, view, ate);
                        }
                        Point += 5;
                    }
                    else
                    {
                        PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        for (int i = 0; i < n; i++)
                            for (int j = 0; j < m; j++)
                                if (selected[i][j] && !ate[i + 1][j + 1])
                                    selected[i][j] = false;

                        printBoard(hei, wid, n, m, 1, view, pic, movingOn, selected, cpy);
                        Point --;
                        Sleep(300);
                    }
                    unSelect(n, m, ate, selected);
                    movingOn[y][x] = true;
                    printBoard(hei, wid, n, m, 0, view, pic, movingOn, selected, cpy);
                    return;
                }
                printBoard(hei, wid, n, m, 0, view, pic, movingOn, selected, cpy);
                cnt++;
            }
            prevKey = key;

        }
    }
}

void updateFile(savefile player);
void choiceLevel(savefile player);

void process(int hei, int wid, int n, int m, char C[200][200], char view[200][200], char pic[200][200], bool ate[200][200], bool movingOn[200][200], bool selected[200][200], char cpy[200][200], savefile &player, const int choosenLevel, bool is_cont)
{
    int y = player.state[choosenLevel - 1].p_, x = player.state[choosenLevel - 1].q_;
    if (!is_cont)
        x = y = 0;
    int Swap = 10 - choosenLevel, Hint = 10 - choosenLevel, Point = (Swap + Hint) * 100 + choosenLevel * 500;
    int TIME = 600 - choosenLevel * 30;
    int timeLeft = TIME;
    bool stop = false;

    if (choosenLevel == 5)
    {
        timeLeft = TIME = 3600;
        Swap = 666;
        Hint = 333;
    }

    int m1, s1;
    time_t now = time('\0');
    tm *t = localtime(&now);
    m1 = t->tm_min;
    s1 = t->tm_sec;

    printInfo(player, Swap, Hint);
    memset(movingOn, false, sizeof(movingOn));
    movingOn[y][x] = true;
    printBoard(hei, wid, n, m, 0, view, pic, movingOn, selected, cpy);
    if (is_cont)
        movingOn[y][x] = false;
    while (!checkEnd(n, m, ate))
    {
        bool swapped = false;
        while (cantMove(hei,wid,n, m, C, view, pic, ate, movingOn, selected, cpy))
        {
            swapped = true;
            refreshArray(hei, wid,n, m, C, view, ate);
            printBoard(hei,wid,n, m, 2, view, pic, movingOn, selected, cpy);
            Sleep(300);
        }
         if (swapped)
        {
            movingOn[y][x] = true;
            printBoard(hei, wid, n, m, 0, view, pic, movingOn, selected, cpy);
            movingOn[y][x] = false;
        }
        move(hei, wid, n, m, y, x,stop, C, view, pic, ate, movingOn, selected, cpy, Swap, Hint, TIME, timeLeft, m1, s1, Point, choosenLevel);
        movingOn[y][x] = false;
        printInfo(player, Swap, Hint);
        if (stop)
        {
            for (int i = 0; i < 5; i++)
                player.state[i].p_ = player.state[i].q_ = -1;

            player.state[choosenLevel - 1].p_ = y;
            player.state[choosenLevel - 1].q_ = x;
            player.record[choosenLevel - 1].points = -2; // Neu dang choi ma out thi k duoc ghi vao thanh tich nua

            int dem = 0;
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    player.state[choosenLevel - 1].board[dem] = C[i][j];
                    dem++;
                }
            }

            updateFile(player);
            displayMenu();
            return;
        }
        if (timeLeft == -1)
            break;
    }

    // Point -= max(0, ((t->tm_min - m1) * 60 + (t->tm_sec - s1))/2); // 2 giay mat 1 point
    // player.maxScore = 0;

    memset(movingOn, false, sizeof(movingOn));
    printBoard(hei, wid,n, m, 0, view, pic, movingOn, selected, cpy);

    Sleep(1234);
    system("cls");

    player.state[choosenLevel - 1].p_ = player.state[choosenLevel - 1].q_ = -1;
    if(is_cont)
        Point = -1;

    if (timeLeft != -1)
    {
        if (Point > player.record[choosenLevel - 1].points)
        {
            player.record[choosenLevel - 1].points = Point;
            player.record[choosenLevel - 1].date.dd = t->tm_mday;
            player.record[choosenLevel - 1].date.mm = t->tm_mon + 1;
            player.record[choosenLevel - 1].date.yy = t->tm_year + 1900;
        }
        if (!is_cont)
            player.record[choosenLevel].points = max(player.record[choosenLevel].points, 0); // Khong stop thi moi uplevel
        
        SetConsoleOutputCP(65001);
        const int heii = 5, widd = 7;
        int BackGroundColor = rand() % 15 + 1;

        char pic[200][200];
        gotoxy(0,0);
        makePic(5,11,heii,widd,pic,5);
        PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
        TextColor(10);
        for(int i = 0; i <= heii * 9; i++)
        {
            for(int j = 0; j <= widd * 21; j++)
            {
                if(j == 0)
                    doTab(0);
                if (j % 2 == 0)
                    TextColor(14);
                else
                    TextColor(7);
                cout <<  pic[i][j];
            }
            cout <<  endl;
        }
        TextColor(3);
        gotoxy(52, 7);
        cout << "__  ______  __  __  _      ______  _  __";
        gotoxy(52, 8);
        cout << "\\ \\/ / __ \\/ / / / | | /| / / __ \\/ |/ /";
        TextColor(7);
        gotoxy(52, 9);
        cout << " \\  / /_/ / /_/ /  | |/ |/ / /_/ /    /";
        gotoxy(52, 10);
        cout << " /_/\\____/\\____/   |__/|__/\\____/_/|_/" << endl;
        gotoxy(50, 12);
        cout << "Congratulation !!! You got: ";
        TextColor(3);
        gotoxy(78, 12);
        cout << Point;
        gotoxy(83, 12);
        TextColor(7);
        cout << " point !!!" << endl;
        gotoxy(64, 13);
        cout << " ╔═══════════╗" << endl;
        gotoxy(64, 14);
        cout << " ║ GAME OVER ║  " << endl;
        gotoxy(64, 15);
        cout << " ╚═══════════╝" << endl;
        updateFile(player);
    }
    else if (TIME == 0)
    {
        SetConsoleOutputCP(65001);
        const int heii = 5, widd = 7;
        int BackGroundColor = rand() % 15 + 1;

        char pic[200][200];
        gotoxy(0,0);
        makePic(5,11,heii,widd,pic,5);
        PlaySound(TEXT("lose.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
        TextColor(10);
        for(int i = 0; i <= heii * 9; i++)
        {
            for(int j = 0; j <= widd * 21; j++)
            {
                if(j == 0)
                    doTab(0);
                if (j % 2 == 0)
                    TextColor(14);
                else
                    TextColor(7);
                cout <<  pic[i][j];
            }
            cout <<  endl;
        }
        TextColor(4);
        gotoxy(52, 7);
        cout << "__  ______  __  __  __   ____  ________";
        gotoxy(52, 8);
        cout << "\\ \\/ / __ \\/ / / / / /  / __ \\/ __/ __/";
        gotoxy(52, 9);
        cout << " \\  / /_/ / /_/ / / /__/ /_/ /\\ \\/ _/";
        gotoxy(52, 10);
        cout << " /_/\\____/\\____/ /____/\\____/___/___/";
        gotoxy(50, 12);
        cout << "You are looser !!! Try again !!!" << endl;
        TextColor(7);
    }

    gotoxy(58, 17);
    TextColor(6);
    cout <<  "Press any key to continue !!!" << endl;
    TextColor(7);

    char ch;
    ch = _getch();

    system("cls");
    
    updateFile(player);
    choiceLevel(player);
}

void updateFile(savefile player)
{
    savefile tmp;
    vector<savefile> adj;
    ifstream fin;
    fin.open("account\\account.dat", ios::binary);
    while (!fin.eof())
    {
        fin.read((char *)&(tmp), sizeof(savefile));
        if (fin.eof())
            break;
        char Name[strlen(tmp.name)], Pass[strlen(tmp.password)];

        for (int i = 0; i < strlen(tmp.name); i++)
            Name[i] = tmp.name[i] ^ tmp.mask;

        for (int i = 0; i < strlen(tmp.password); i++)
            Pass[i] = tmp.password[i] ^ tmp.mask;

        if (strcmp(Name, player.name) == 0 && strcmp(Pass, player.password) == 0)
        {
            for (int i = 0; i < 5; i++)
            {
                if (player.record[i].points != -2)
                {
                    if (player.record[i].points >= tmp.record[i].points)
                    {
                        tmp.record[i].points = player.record[i].points;
                        tmp.record[i].date.dd = player.record[i].date.dd;
                        tmp.record[i].date.mm = player.record[i].date.mm;
                        tmp.record[i].date.yy = player.record[i].date.yy;
                    }
                }

                tmp.state[i].q = player.state[i].q;
                tmp.state[i].p = player.state[i].p;

                tmp.state[i].q_ = player.state[i].q_;
                tmp.state[i].p_ = player.state[i].p_;

                if (player.state[i].p_ != -1 && player.state[i].q_ != -1)
                {
                    for (int j = 0; j < tmp.state[i].q * tmp.state[i].p; j++)
                        tmp.state[i].board[j] = player.state[i].board[j];
                }
                else
                    for (int j = 0; j < tmp.state[i].q * tmp.state[i].p; j++)
                        tmp.state[i].board[j] = '\0';
            }
        }
        adj.push_back(tmp);
    }
    fin.close();

    ofstream fout;
    fout.open("account\\account.dat", ios::binary);
    for (int i = 0; i < adj.size(); i++)
        fout.write((char *)&(adj[i]), sizeof(savefile));
    fout.close();
}
