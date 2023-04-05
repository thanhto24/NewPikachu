#pragma once
#include "header.h"
#include "player.h"
#include "saveFile.h"
#include "level.h"

void makeLevel(int hei, int wid, int n, int m, int choosenLevel, savefile &player, bool is_cont);

void doContinue(savefile player)
{
    for(int i = 0; i < 5; i++)
    {
        if(player.state[i].p_!=-1)
        {
            makeLevel(5,11,player.state[i].p,player.state[i].q,i+1,player,1);
            return;
        }
    }
}