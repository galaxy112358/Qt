#include "ReversiGame.h"

//ReversiAgent
ReversiAgent::ReversiAgent(QString TYPENAME, QPoint p) : ChessAgent(TYPENAME,p) {}

//ReversiGame
ReversiGame::ReversiGame(int first)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            board[i][j] = 0;
            //reversedP[i][j] = 0;
        }
        avaiDirection[i] = 0;
    }
    //setNum = 0;
    turn = first;
    score[0] = 0;
    score[1] = 0;
    total = 0;
    lastPos.x = -1; lastPos.y = -1;
    agent[0] = nullptr;
    agent[1] = nullptr;
}

ReversiGame::~ReversiGame()
{
    if (agent[0] != nullptr) delete agent[0];
    if (agent[1] != nullptr) delete agent[1];
}

void ReversiGame::restart(int first)
{
    if (agent[0] != nullptr) delete agent[0];
    if (agent[1] != nullptr) delete agent[1];
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            board[i][j] = 0;
            //reversedP[i][j] = 0;
        }
        avaiDirection[i] = 0;
    }
    board[3][3] = 1;
    board[4][4] = 1;
    board[3][4] = 2;
    board[4][3] = 2;
    //setNum = 0;
    turn = first;
    score[0] = 0;
    score[1] = 0;
    total = 0;
    lastPos.x = -1; lastPos.y = -1;
    agent[0] = new ReversiAgent("ReversiPlayer 1",QPoint(500, 100));
    QObject::connect(agent[0], &ChessAgent::agentCreated, [=]() {
        agent[1] = new ReversiAgent("ReversiPlayer 2", QPoint(500, 100));
        QObject::connect(agent[1], &ChessAgent::agentCreated,[=](){
            this->emit agentsCreated();
        });
    });
}

void ReversiGame::resetGameState(int first)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            board[i][j] = 0;
            //reversedP[i][j] = 0;
        }
        avaiDirection[i] = 0;
    }
    board[3][3] = 1;
    board[4][4] = 1;
    board[3][4] = 2;
    board[4][3] = 2;
    //setNum = 0;
    turn = first;
    lastPos.x = -1; lastPos.y = -1;
}

void ReversiGame::changeGameState(POINT P)
{
    int x = P.y / 8, y = P.y % 8;
    int tx = 0, ty = 0;
    if(avaiDirection[0])
        for(int i = 1;; i++)
        {
            tx = x - i; ty = y - i;
            if(tx < 0 or tx > 7 or ty < 0 or ty > 7) break;
            if(board[tx][ty] == (turn + 1) % 2 + 1)
                board[tx][ty] = turn + 1;
            else break;
        }
    if(avaiDirection[1])
        for(int i = 1;; i++)
        {
            tx = x; ty = y - i;
            if(tx < 0 or tx > 7 or ty < 0 or ty > 7) break;
            if(board[tx][ty] == (turn + 1) % 2 + 1)
                board[tx][ty] = turn + 1;
            else break;
        }
    if(avaiDirection[2])
        for(int i = 1;; i++)
        {
            tx = x + i; ty = y - i;
            if(tx < 0 or tx > 7 or ty < 0 or ty > 7) break;
            if(board[tx][ty] == (turn + 1) % 2 + 1)
                board[tx][ty] = turn + 1;
            else break;
        }
    if(avaiDirection[3])
        for(int i = 1;; i++)
        {
            tx = x + i; ty = y;
            if(tx < 0 or tx > 7 or ty < 0 or ty > 7) break;
            if(board[tx][ty] == (turn + 1) % 2 + 1)
                board[tx][ty] = turn + 1;
            else break;
        }
    if(avaiDirection[4])
        for(int i = 1;; i++)
        {
            tx = x + i; ty = y + i;
            if(tx < 0 or tx > 7 or ty < 0 or ty > 7) break;
            if(board[tx][ty] == (turn + 1) % 2 + 1)
                board[tx][ty] = turn + 1;
            else break;
        }
    if(avaiDirection[5])
        for(int i = 1;; i++)
        {
            tx = x; ty = y + i;
            if(tx < 0 or tx > 7 or ty < 0 or ty > 7) break;
            if(board[tx][ty] == (turn + 1) % 2 + 1)
                board[tx][ty] = turn + 1;
            else break;
        }
    if(avaiDirection[6])
        for(int i = 1;; i++)
        {
            tx = x - i; ty = y + i;
            if(tx < 0 or tx > 7 or ty < 0 or ty > 7) break;
            if(board[tx][ty] == (turn + 1) % 2 + 1)
                board[tx][ty] = turn + 1;
            else break;
        }
    if(avaiDirection[7])
        for(int i = 1;; i++)
        {
            tx = x - i; ty = y;
            if(tx < 0 or tx > 7 or ty < 0 or ty > 7) break;
            if(board[tx][ty] == (turn + 1) % 2 + 1)
                board[tx][ty] = turn + 1;
            else break;
        }

    board[x][y] = turn + 1;
    lastPos = P;
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
        {
            POINT p;
            p.x = 0;
            p.y = i * 8 + j;
            if(judge(p, (turn + 1) % 2) and board[i][j] == 0)
            {
                turn = (turn + 1) % 2;
                return;
            }
        }
}

int ReversiGame::judge(POINT P, int turn)
{
    for(int i = 0; i < 8; i++)
        avaiDirection[i] = 0;
    int x = P.y / 8, y = P.y % 8;
    int tx = 0, ty = 0;
    for(int i = 1;; i++)
    {
        tx = x - i; ty = y - i;
        if(tx < 0 or tx > 7 or ty < 0 or ty > 7) break;
        if(board[tx][ty] == 0) break;
        if(i == 1 and board[tx][ty] != (turn + 1) % 2 + 1) break;
        if(board[tx][ty] == turn + 1) avaiDirection[0] = 1;
    }
    for(int i = 1;; i++)
    {
        tx = x; ty = y - i;
        if(tx < 0 or tx > 7 or ty < 0 or ty > 7) break;
        if(board[tx][ty] == 0) break;
        if(i == 1 and board[tx][ty] != (turn + 1) % 2 + 1) break;
        if(board[tx][ty] == turn + 1) avaiDirection[1] = 1;
    }
    for(int i = 1;; i++)
    {
        tx = x + i; ty = y - i;
        if(tx < 0 or tx > 7 or ty < 0 or ty > 7) break;
        if(board[tx][ty] == 0) break;
        if(i == 1 and board[tx][ty] != (turn + 1) % 2 + 1) break;
        if(board[tx][ty] == turn + 1) avaiDirection[2] = 1;
    }
    for(int i = 1;; i++)
    {
        tx = x + i; ty = y;
        if(tx < 0 or tx > 7 or ty < 0 or ty > 7) break;
        if(board[tx][ty] == 0) break;
        if(i == 1 and board[tx][ty] != (turn + 1) % 2 + 1) break;
        if(board[tx][ty] == turn + 1) avaiDirection[3] = 1;
    }
    for(int i = 1;; i++)
    {
        tx = x + i; ty = y + i;
        if(tx < 0 or tx > 7 or ty < 0 or ty > 7) break;
        if(board[tx][ty] == 0) break;
        if(i == 1 and board[tx][ty] != (turn + 1) % 2 + 1) break;
        if(board[tx][ty] == turn + 1) avaiDirection[4] = 1;
    }
    for(int i = 1;; i++)
    {
        tx = x; ty = y + i;
        if(tx < 0 or tx > 7 or ty < 0 or ty > 7) break;
        if(board[tx][ty] == 0) break;
        if(i == 1 and board[tx][ty] != (turn + 1) % 2 + 1) break;
        if(board[tx][ty] == turn + 1) avaiDirection[5] = 1;
    }
    for(int i = 1;; i++)
    {
        tx = x - i; ty = y + i;
        if(tx < 0 or tx > 7 or ty < 0 or ty > 7) break;
        if(board[tx][ty] == 0) break;
        if(i == 1 and board[tx][ty] != (turn + 1) % 2 + 1) break;
        if(board[tx][ty] == turn + 1) avaiDirection[6] = 1;
    }
    for(int i = 1;; i++)
    {
        tx = x - i; ty = y;
        if(tx < 0 or tx > 7 or ty < 0 or ty > 7) break;
        if(board[tx][ty] == 0) break;
        if(i == 1 and board[tx][ty] != (turn + 1) % 2 + 1) break;
        if(board[tx][ty] == turn + 1) avaiDirection[7] = 1;
    }
    for(int i = 0; i < 8; i++)
        if(avaiDirection[i]) return 1;
    return 0;
}
int ReversiGame::judgeLegal(POINT P)
{
    int x = P.y / 8, y = P.y % 8;
    if (board[x][y] != 0)//落子重合错误
        return 0;
    else if (!judge(P, turn))
        return 0;
    else
        return 1;
}

int ReversiGame::judgeEnd()
{
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
        {
            POINT p;
            p.x = 0;
            p.y = i * 8 + j;
            if((judge(p, 0) or judge(p, 1)) and board[i][j] == 0)
                return 0;
        }
    return countN();
}

int ReversiGame::countN()
{
    int n[2] = {0};
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if(board[i][j]) n[board[i][j] - 1]++;
    if(n[0] > n[1]) return 1;
    else if(n[0] < n[1]) return 2;
    else return -1;
}
