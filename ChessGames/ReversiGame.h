#pragma once

#include "ChessGame.h"

class ReversiGame :public ChessGame
{
public:
    int board[8][8];//对局棋盘信息(存的是玩家号，即1或2)
    bool avaiDirection[8];
    //int reversedP[8][8], setNum;
    ReversiGame(int first = 0);
    ~ReversiGame();
    virtual void restart(int first = 0);
    virtual void resetGameState(int first = 0);
    virtual void changeGameState(POINT P);
    int judge(POINT P, int turn);
    int countN();
    virtual int judgeLegal(POINT P);
    virtual int judgeEnd();

};

class ReversiAgent :public ChessAgent
{
public:
    ReversiAgent(QString TYPENAME, QPoint p);
};
