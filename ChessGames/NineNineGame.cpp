#include "NineNineWindow.h"
#include "NineNineGame.h"

//NineNineGame
NineNineGame::NineNineGame(int first)
{
	for (int i = 0; i < 9; i++) {
		occupy[i] = 0;
		available[i] = 0;
		for (int j = 0; j < 9; j++) board[i][j] = 0;
	}
	turn = first;
	startBoard = 0;
	score[0] = 0;
	score[1] = 0;
	total = 0;
	lastPos.x = -1; lastPos.y = startBoard;
	available[startBoard] = 1;
	startBoard++;
	startBoard %= 9;
	agent[0] = nullptr;
	agent[1] = nullptr;
}

NineNineGame::~NineNineGame()
{
	if (agent[0] != nullptr) delete agent[0];
	if (agent[1] != nullptr) delete agent[1];
}

void NineNineGame::restart(int first)
{
	if (agent[0] != nullptr) delete agent[0];
	if (agent[1] != nullptr) delete agent[1];
	for (int i = 0; i < 9; i++) {
		occupy[i] = 0;
		available[i] = 0;
		for (int j = 0; j < 9; j++) board[i][j] = 0;
	}
	turn = first;
	startBoard = 0;
    score[0] = 0;
	score[1] = 0;
	total = 0;
	lastPos.x = -1; lastPos.y = startBoard;
	available[startBoard] = 1;
	startBoard++;
	startBoard %= 9;
	agent[0] = new NineNineAgent("Player 1", QPoint(500, 100));
	QObject::connect(agent[0], &ChessAgent::agentCreated, [=]() {
		agent[1] = new NineNineAgent("Player 2", QPoint(500, 100));
        QObject::connect(agent[1], &ChessAgent::agentCreated,[=](){
            this->emit agentsCreated();
        });
		});
}

void NineNineGame::resetGameState(int first)
{
	for (int i = 0; i < 9; i++) {
		occupy[i] = 0;
		available[i] = 0;
		for (int j = 0; j < 9; j++) board[i][j] = 0;
	}
	turn = first;
	lastPos.x = -1; lastPos.y = startBoard;
	available[startBoard] = 1;
	startBoard++;
	startBoard %= 9;
}

int NineNineGame::judgeLegal(POINT P)
{
	if (available[P.x] and board[P.x][P.y] == 0) return 1;
	else return 0;
}

int NineNineGame::judgeOccupy(int x)
{
	//返回占领x棋盘的玩家号，若无则返回0
	//返回3说明无处可下
	int i = 0;
	for (i = 0; i < 3; i++) {
		if (board[x][i * 3] != 0 and
			board[x][i * 3] == board[x][1 + i * 3] and
			board[x][i * 3] == board[x][2 + i * 3])
			return board[x][i * 3];
		if (board[x][i] != 0 and
			board[x][i] == board[x][i + 3] and
			board[x][i] == board[x][i + 6])
			return board[x][i];
	}
	if (board[x][4] != 0) {
		if (board[x][0] == board[x][4] and
			board[x][8] == board[x][4])
			return board[x][4];
		if (board[x][2] == board[x][4] and
			board[x][6] == board[x][4])
			return board[x][4];
	}
	for (int i = 0; i < 9; i++)
		if (board[x][i] == 0)
			return 0;
	return 3;
}

void NineNineGame::changeGameState(POINT P)
{
	board[P.x][P.y] = turn + 1;

	occupy[P.x] = judgeOccupy(P.x);

	for (int i = 0; i < 9; i++)
		available[i] = 0;
	if (occupy[P.y] == 0)
		available[P.y] = 1;
	else 
	{
		for (int i = 0; i < 9; i++)
			if (occupy[i] == 0)
				available[i] = 1;
	}

	lastPos = P;

	turn = (turn + 1) % 2;
}

int NineNineGame::judgeEnd()
{
	//判断游戏是否结束，返回获胜方（平局返回3），还能继续返回0
	bool flag = 0;
	int i = 0, j = 0;
	for (i = 0; i < 3; i++) {
		if (occupy[i * 3] != 3 and occupy[i * 3] != 0 and occupy[i * 3] == occupy[1 + i * 3] and occupy[i * 3] == occupy[2 + i * 3]) return occupy[i * 3];
		if (occupy[i] != 3 and occupy[i] != 0 and occupy[i] == occupy[i + 3] and occupy[i] == occupy[i + 6]) return occupy[i];
	}
	if (occupy[4] != 0 and occupy[4] != 3) {
		if (occupy[0] == occupy[4] and occupy[8] == occupy[4]) return occupy[4];
		if (occupy[2] == occupy[4] and occupy[6] == occupy[4]) return occupy[4];
	}
	for (i = 0; i < 9; i++)
		if (available[i])
			for (j = 0; j < 9; j++)
				if (board[i][j] == 0)
					flag = 1;
	if (flag == 0) return 3;
	return 0;
}

//NineNineAgent
NineNineAgent::NineNineAgent(QString TYPENAME, QPoint p) :ChessAgent(TYPENAME, p) {}
