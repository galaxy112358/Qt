#pragma once

#include "ChessGame.h"

class GoBangGame :public ChessGame
{
public:
    int board[15][15];//对局棋盘信息(存的是玩家号，即1或2)

    GoBangGame(int first = 0);
    ~GoBangGame();
    virtual void restart(int first = 0);
    virtual void resetGameState(int first = 0);
    virtual void changeGameState(POINT P);
    virtual int judgeLegal(POINT P);
    virtual int judgeEnd();

};

class GoBangAgent :public ChessAgent
{
public:
    GoBangAgent(QString TYPENAME, QPoint p);
};
