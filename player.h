#pragma once

#define NAMESIZE 50
#define PASSSIZE 50
#define BOARDSIZE 999
#define URLSIZE 100

struct State
{                                  
    int p, q;                      
    int p_, q_;                    
    char board[BOARDSIZE];         
    char file_background[URLSIZE]; 
};

struct Date
{
    int dd, mm, yy;
};

struct Record
{
    Date date;    // Date of completed record
    int points; // points achieved
};

struct savefile
{
    char mask;               // You are required to transfer all char-type variables by performing xor each with
    char name[NAMESIZE];     // username
    char password[PASSSIZE]; // password
    Record record[5]; // List of sorted best records
    State state[5];   // List of save state
}; 