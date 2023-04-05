#pragma pack(1)
#include "header.h"
#include "player.h"
#include "login.h"

void displayMenu();

bool neverExist(char S[])
{
    savefile tmp;
    ifstream fin;
    fin.open("account\\account.dat", ios::binary);
    while(!fin.eof())
    {
        fin.read((char *) &(tmp), sizeof(savefile));

        if(fin.eof())
        break;

        for(int i = 0; i < strlen(tmp.name); i++)
            tmp.name[i] = tmp.name[i] ^ tmp.mask;

        if(strcmp(S,tmp.name) == 0)
        {
            fin.close();
            return false;
        }    
    }
    fin.close();
    return true;
}

void printSignUp()
{
    system("cls");
    savefile dangky;
    dangky.mask = '*';
    
    PlaySound(TEXT("background1.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    SetConsoleOutputCP(65001);
    const int heii = 5, widd = 7;
    // char pic[heii hei - (heii)+1][widd * wid - (widd - 2) - 7+1];
    char pic[200][200];
    gotoxy(0,2);
    makePic(5,11,heii,widd,pic,7);
    TextColor(12);
    for(int i = 0; i <= heii * 2 - 2; i++)
    {
        if (i > (heii * 5 - (heii)) / 2)
            TextColor(15);
        for(int j = 0; j <= widd * 17 - (widd - 2) - 6; j++)
        {
            if(j==0)
            {
                doTab(6);
                cout << "    ";
            }
            cout <<  pic[i][j];
        }
        cout <<  endl;
    }

    int BackGroundColor = rand() % 15 + 1;
    makePic(5,11,heii,widd,pic,5);
    TextColor(10);
    for(int i = 0; i <= heii * 6; i++)
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

    gotoxy(0, 10);
    doTab(6);
    TextColor(5);
    SetConsoleOutputCP(65001);
    cout << "╔═════════════════════════════════════════════════════════════════╗" << endl;
    doTab(6);
    cout << "║            TYPE YOUR ACCOUNT INFORMATION TO SIGN UP !!!         ║" << endl;
    doTab(6);
    cout << "╚═════════════════════════════════════════════════════════════════╝" << endl;
    TextColor(7);

    cout << endl;
    doTab(7);
    cout <<  "Username: ";
    gets(dangky.name);

    if(strlen(dangky.name) < 3)
    {
        PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
        TextColor(4);
        cout << endl;
        doTab(7);
        cout <<  "Username length must be greater than 3 !!! Try another !!!" << endl;
        Sleep(1500);
        TextColor(7);
        printSignUp();
        return;
    }

    if(strlen(dangky.name) > 20)
    {
        PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
        TextColor(4);
        cout << endl;
        doTab(7);
        cout << "Username length must be smaller than 20! Try another !!!" << endl;
        Sleep(1500);
        TextColor(7);
        printSignUp();
        return;
    }

    if(!neverExist(dangky.name))
    {
        PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
        TextColor(4);
        cout << endl;
        doTab(7);
        cout <<  "This username was existed! Try another !!!" << endl;
        Sleep(1500);
        TextColor(7);
        printSignUp();
        return;
    }
    
    string pass = "";

    char ch;
    int dem = 0;

    gotoxy(0, 16);
    doTab(7);
    cout <<  "Password: ";

    while((ch = _getch()) != 13 && ch != ' ' && pass.size() < 20)
    {
        dem++;
        if(ch == 8 && pass.size()>0)
            pass.erase(pass.begin() + pass.size()-1);
        else
        if(ch != 8 )
        pass += ch;
        gotoxy(0,16);
        doTab(7);
        cout <<  "Password: ";
        for(int i = 0; i < pass.size(); i++)
            cout << '*';
        for(int i = pass.size(); i <= dem; i++)
            cout << ' ';
        cout << endl;
    }
    strcpy(dangky.password,pass.c_str());

    int x = 1;

    TextColor(14);
    gotoxy(0, 18);
    doTab(7);
    cout << "Press [ S ] to show password, or [ H ] to hide ...";

    while(1)
    {
        if (kbhit()) // Kiểm tra xem có bấm phím kg
        {
            gotoxy(0,5);

            char key = getch(); // Lấy ký tự người dùng vừa bấm

            if (toupper(key)== 'A'||toupper(key)== 'D'||key==75||key==77) // Di chuyển trái
            {
                ++x;
            }
            

            if(key == 13|| toupper(key) == 'S' || toupper(key) == 'H')
            {
                if(x&1||toupper(key)=='S')
                {
                    TextColor(7);
                    gotoxy(0, 16);
                    doTab(7);
                    cout <<  "Password: " << pass;
                }
                gotoxy(0, 17);
                doTab(7);
                cout <<  endl;
                break;
            }
            
            gotoxy(0, 18);
            doTab(7);
            if(x&1)
                cout << "Press [ S ] to show password, or [ H ] to hide ...";
            else
                cout << "Press [ S ] to show password, or [ H ] to hide ...";
            cout <<  endl;
        }

    }
    
    cout << endl;
    gotoxy(0, 20);
    doTab(7);
    TextColor(11);
    cout << "Are you sure to sign up this account ???" << endl;
    doTab(7);
    cout << "Press A to sign up again or others key to continue !!!" << endl;
    TextColor(7);

    ch = _getch();
    if(toupper(ch)=='A')
    {
        PlaySound(TEXT("match.wav"), NULL, SND_FILENAME | SND_ASYNC);
        return void(printSignUp());
    }

    for(int i = 0; i < strlen(dangky.name); i++)
        dangky.name[i] ^= dangky.mask;

    for(int i = 0; i < strlen(dangky.password); i++)
        dangky.password[i] ^= dangky.mask;

    for(int i = 0; i < 5; i++)
    {
        dangky.state[i].p = dangky.state[i].q = dangky.record[i].points = dangky.record[i].date.dd = dangky.record[i].date.mm = dangky.record[i].date.yy = dangky.state[i].p_ = dangky.state[i].q_ = -1;
        for(int j = 0; j < 999; j++)
            dangky.state[i].board[j] = '\0';
        for(int j = 0; j < 100; j++)
            dangky.state[i].file_background[j] = '\0';
    }
    dangky.record[0].points = 0;

    // Ghi vao file
    ofstream fout;

    fout.open("account\\account.dat",ios::binary | ios::app);
    fout.write((char *) &(dangky), sizeof(savefile));
    fout.close();

    TextColor(6);
    cout << endl;
    PlaySound(TEXT("match.wav"), NULL, SND_FILENAME | SND_ASYNC);
    doTab(7);
    cout <<  "Sign up sucessfully !!!" << endl;
    doTab(7);
    cout <<  "Press L to Login or others key to back to menu !!!" << endl;
    TextColor(7);
    
    ch = _getch();
     if(toupper(ch)=='L')
        printLogin();
    else
    displayMenu();
}
