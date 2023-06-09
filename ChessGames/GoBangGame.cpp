#include "GoBangGame.h"

//GoBangAgent
GoBangAgent::GoBangAgent(QString TYPENAME, QPoint p) :ChessAgent(TYPENAME, p) {}

//GoBangGame
GoBangGame::GoBangGame(int first)
{
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            board[i][j] = 0;
    turn = first;
    score[0] = 0;
    score[1] = 0;
    total = 0;
    lastPos.x = -1; lastPos.y = -1;
    agent[0] = nullptr;
    agent[1] = nullptr;
}

GoBangGame::~GoBangGame()
{
    if (agent[0] != nullptr) delete agent[0];
    if (agent[1] != nullptr) delete agent[1];
}

void GoBangGame::restart(int first)
{
    if (agent[0] != nullptr) delete agent[0];
    if (agent[1] != nullptr) delete agent[1];
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            board[i][j] = 0;
    turn = first;
    score[0] = 0;
    score[1] = 0;
    total = 0;
    lastPos.x = -1; lastPos.y = -1;
    agent[0] = new GoBangAgent("GoBangPlayer 1",QPoint(500, 100));
    QObject::connect(agent[0], &ChessAgent::agentCreated, [=]() {
        agent[1] = new GoBangAgent("GoBangPlayer 2", QPoint(500, 100));
        QObject::connect(agent[1], &ChessAgent::agentCreated,[=](){
            this->emit agentsCreated();
        });
    });
}

void GoBangGame::resetGameState(int first)
{
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            board[i][j] = 0;
    turn = first;
    lastPos.x = -1; lastPos.y = -1;
}

void GoBangGame::changeGameState(POINT P)
{
    int x = P.y / 15, y = P.y % 15;
    board[x][y] = turn + 1;
    lastPos = P;
    turn = (turn + 1) % 2;
}

int GoBangGame::judgeLegal(POINT P)
{
    int x = P.y / 15, y = P.y % 15;
    if(board[x][y]) return 0;
    else return 1;
}

int GoBangGame::judgeEnd()
{
    bool flag = 0;
    for(int i = 1; i < 15; i++)
        for(int j = 1; j < 15; j++)
            if(board[i][j]==0) flag = 1;
    if(flag == 0) return -1;

    int N[8] = { 0 };
    int x = lastPos.y / 15, y = lastPos.y % 15;
    int standard = board[x][y];
    int tx = 0, ty = 0;
    for(int i = 1;; i++)
    {
        tx = x - i; ty = y - i;
        if(tx < 0 or tx > 14 or ty < 0 or ty > 14)
            break;
        if(board[tx][ty] != standard) break;
        N[0]++;
    }
    for(int i = 1;; i++)
    {
        tx = x; ty = y - i;
        if(tx < 0 or tx > 14 or ty < 0 or ty > 14)
            break;
        if(board[tx][ty] != standard) break;
        N[1]++;
    }
    for(int i = 1;; i++)
    {
        tx = x + i; ty = y - i;
        if(tx < 0 or tx > 14 or ty < 0 or ty > 14)
            break;
        if(board[tx][ty] != standard) break;
        N[2]++;
    }
    for(int i = 1;; i++)
    {
        tx = x + i; ty = y;
        if(tx < 0 or tx > 14 or ty < 0 or ty > 14)
            break;
        if(board[tx][ty] != standard) break;
        N[3]++;
    }
    for(int i = 1;; i++)
    {
        tx = x + i; ty = y + i;
        if(tx < 0 or tx > 14 or ty < 0 or ty > 14)
            break;
        if(board[tx][ty] != standard) break;
        N[4]++;
    }
    for(int i = 1;; i++)
    {
        tx = x; ty = y + i;
        if(tx < 0 or tx > 14 or ty < 0 or ty > 14)
            break;
        if(board[tx][ty] != standard) break;
        N[5]++;
    }
    for(int i = 1;; i++)
    {
        tx = x - i; ty = y + i;
        if(tx < 0 or tx > 14 or ty < 0 or ty > 14)
            break;
        if(board[tx][ty] != standard) break;
        N[6]++;
    }
    for(int i = 1;; i++)
    {
        tx = x - i; ty = y;
        if(tx < 0 or tx > 14 or ty < 0 or ty > 14)
            break;
        if(board[tx][ty] != standard) break;
        N[7]++;
    }

    if(N[0] + N[4] >= 4 or N[1] + N[5] >= 4 or N[2] + N[6] >= 4 or N[3] + N[7] >= 4) return standard;
    else return 0;
}
