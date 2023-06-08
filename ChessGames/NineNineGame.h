#pragma once

#include "ChessGame.h"

class NineNineGame :public ChessGame
{
public:
	int occupy[9], board[9][9];//�Ծ�������Ϣ(�������Һţ���1��2)
	int available[9];//��ǰ�غ���Ϣ(turn�����0��1)
	int startBoard;//��ʼ���̣���˳������

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
