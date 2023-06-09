#pragma once

#include "ChessGame.h"

class NineGridGame :public ChessGame
{
public:
    int board[9];//对局棋盘信息(存的是玩家号，即1或2)

    NineGridGame(int first = 0);
    ~NineGridGame();
    virtual void restart(int first = 0);
    virtual void resetGameState(int first = 0);
    virtual void changeGameState(POINT P);
    virtual int judgeLegal(POINT P);
    virtual int judgeEnd();

};

class NineGridAgent :public ChessAgent
{
public:
    NineGridAgent(QString TYPENAME, QPoint p);
};
