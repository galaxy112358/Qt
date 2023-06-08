#pragma once

#include "ChessGame.h"

class NineNineGame :public ChessGame
{
public:
	int occupy[9], board[9][9];//对局棋盘信息(存的是玩家号，即1或2)
	int available[9];//当前回合信息(turn存的是0或1)
	int startBoard;//起始棋盘（按顺序来）

	NineNineGame(int first = 0);
	~NineNineGame();
    virtual void restart(int first = 0);
	virtual void resetGameState(int first = 0);
	virtual void changeGameState(POINT P);
	int judgeOccupy(int x);
	virtual int judgeLegal(POINT P);
	virtual int judgeEnd();

};

class NineNineAgent :public ChessAgent
{
public:
	NineNineAgent(QString TYPENAME, QPoint p); 
};
