#pragma once
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#pragma comment(lib, "winmm.lib")
#define ppc(a,n,m) a = new char * [n]; for(int i = 0; i < n; i++) a[i] = new char [m]
#define ppb(a,n,m) a = new bool * [n]; for(int i = 0; i < n; i++) a[i] = new bool [m]
#define ii pair<int, int>
#define f first
#define s second 
#define mp make_pair

// SOUNDTRACK
#define MOVE_SOUND 0
#define ENTER_SOUND 1
#define ERROR_SOUND 2
#define WIN_SOUND 4
#define BACKGROUND_SOUND 5
#define EFFECT_SOUND 6

// COLOR CODE
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

using namespace std;

void gotoxy(int x, int y) 
{ 
    COORD coord;
    coord.X = x; 
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void TextColor(int x) // X là mã màu
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}
