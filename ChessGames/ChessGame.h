#pragma once

#include "Basic.h"

class ChessAgent : public QObject
{
    Q_OBJECT
public:
	ChessAgent(QString TYPENAME, QPoint p);
	~ChessAgent();

	MLabel* info;
	int type;
	QString name;
	QColor color;
	int skin;

signals:
	void agentCreated();
};

class ChessGame : public QObject
{
    Q_OBJECT
public:
	ChessAgent* agent[2];//对战双方
	int score[2], total;//总局数与双方得分
	int turn;//谁的回合
	POINT lastPos;//上一落子
    virtual ~ChessGame();
    virtual void restart(int first = 0) = 0;
	virtual void resetGameState(int first = 0) = 0;
	virtual void changeGameState(POINT P) = 0;
	virtual int judgeLegal(POINT P) = 0;
    virtual int judgeEnd() = 0;
signals:
    void agentsCreated();
};
