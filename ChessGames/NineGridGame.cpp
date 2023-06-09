#include "NineGridGame.h"

//NineGridAgent
NineGridAgent::NineGridAgent(QString TYPENAME, QPoint p) :ChessAgent(TYPENAME, p) {}

//NineGridGame
NineGridGame::NineGridGame(int first)
{
    for (int i = 0; i < 9; i++)
            board[i] = 0;
    turn = first;
    score[0] = 0;
    score[1] = 0;
    total = 0;
    lastPos.x = -1; lastPos.y = -1;
    agent[0] = nullptr;
    agent[1] = nullptr;
}

NineGridGame::~NineGridGame()
{
    if (agent[0] != nullptr) delete agent[0];
    if (agent[1] != nullptr) delete agent[1];
}

void NineGridGame::restart(int first)
{
    if (agent[0] != nullptr) delete agent[0];
    if (agent[1] != nullptr) delete agent[1];
    for (int i = 0; i < 9; i++)
            board[i] = 0;
    turn = first;
    score[0] = 0;
    score[1] = 0;
    total = 0;
    lastPos.x = -1; lastPos.y = -1;
    agent[0] = new NineGridAgent("NineGridPlayer 1",QPoint(500, 100));
    QObject::connect(agent[0], &ChessAgent::agentCreated, [=]() {
        agent[1] = new NineGridAgent("NineGridPlayer 2", QPoint(500, 100));
        QObject::connect(agent[1], &ChessAgent::agentCreated,[=](){
            this->emit agentsCreated();
        });
    });
}

void NineGridGame::resetGameState(int first)
{
    for (int i = 0; i < 9; i++)
            board[i] = 0;
    turn = first;
    lastPos.x = -1; lastPos.y = -1;
}

void NineGridGame::changeGameState(POINT P)
{
    board[P.y] = turn + 1;
    lastPos = P;
    turn = (turn + 1) % 2;
}

int NineGridGame::judgeLegal(POINT P)
{
    if(board[P.y]) return 0;
    else return 1;
}

int NineGridGame::judgeEnd()
{
    bool flag = 0;
    for (int i = 0; i < 3; i++) {
            if (board[i * 3] != 3 and board[i * 3] != 0 and board[i * 3] == board[1 + i * 3] and board[i * 3] == board[2 + i * 3]) return board[i * 3];
            if (board[i] != 3 and board[i] != 0 and board[i] == board[i + 3] and board[i] == board[i + 6]) return board[i];
    }
    if (board[4] != 0 and board[4] != 3) {
            if (board[0] == board[4] and board[8] == board[4]) return board[4];
            if (board[2] == board[4] and board[6] == board[4]) return board[4];
    }
    for(int i = 0; i < 9; i++)
            if(board[i] == 0) flag = 1;
    if(flag == 0)
        return -1;
    return 0;
}
