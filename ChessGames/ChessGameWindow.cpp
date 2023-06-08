#include "ChessGameWindow.h"

ChessGameWindow::ChessGameWindow(QWidget* parent, int HEADDISTANCE, int SIDEDISTANCE, int VERTICALNUM, int HORIZONTALNUM, int VERTICALDISTANCE, int HORIZONTALDISTANCE, int VERTICALUNITNUM, int HORIZONTALUNITNUM, int VERTICALSIDELENGTH, int HORIZONTALSIDELENGTH, int SIDEWIDTH, int INSIDEWIDTH) : QWidget(parent)
{
    setMouseTracking(true);
    drawer.set(HEADDISTANCE, SIDEDISTANCE, VERTICALNUM, HORIZONTALNUM, VERTICALDISTANCE, HORIZONTALDISTANCE, VERTICALUNITNUM, HORIZONTALUNITNUM, VERTICALSIDELENGTH, HORIZONTALSIDELENGTH, SIDEWIDTH, INSIDEWIDTH);
    int ButtonsStart_X = HORIZONTALNUM * (HORIZONTALUNITNUM * HORIZONTALSIDELENGTH + HORIZONTALDISTANCE) - HORIZONTALDISTANCE + SIDEDISTANCE + 50;
    int ButtonsStart_Y = HEADDISTANCE + 25;
    int Button_L = 0, Button_H = 0, Label_L = 0, Label_H = HEADDISTANCE / 2;
    if (HORIZONTALSIDELENGTH > 50)
    {
        Button_L = HORIZONTALSIDELENGTH * 2;
        Label_L = HORIZONTALSIDELENGTH * 7;
    }
    else
    {
        Button_L = 100;
        Label_L = 350;
    }
    if (VERTICALSIDELENGTH > 40)
        Button_H = VERTICALSIDELENGTH - 10;
    else Button_H = 30;
    int LabelStart_X = (ButtonsStart_X - 50 + SIDEDISTANCE) / 2 - Label_L / 2;
    int LabelStart_Y = (HEADDISTANCE - Label_H) / 2;
    exit = new MPushButton(this, QRect(ButtonsStart_X, ButtonsStart_Y, Button_L, Button_H), Button_H / 4);
    exit->setText("Menu");
    newStart = new MPushButton(this, QRect(ButtonsStart_X, ButtonsStart_Y + Button_H * 3 / 2, Button_L, Button_H), Button_H / 4);
    newStart->setText("New Start");
    newGame = new MPushButton(this, QRect(ButtonsStart_X, ButtonsStart_Y + Button_H * 3, Button_L, Button_H), Button_H / 4);
    newGame->hide();
    newGame->setText("New Game");
    atMid = new MLabel(this, QRect(LabelStart_X + HORIZONTALSIDELENGTH, LabelStart_Y, Label_L, Label_H), Label_H / 4, Qt::red, Qt::transparent, 16);
    atMid->setText("Press New Start to start !");
    rounds = new MLabel(this, QRect(SIDEDISTANCE / 3, LabelStart_Y, Label_L/3, Label_H), Label_H / 4, Qt::black, Qt::transparent, 16);
    rounds->hide();
    scores = new MLabel(this, QRect(ButtonsStart_X - 25, LabelStart_Y, Label_L/3, Label_H), Label_H / 4, Qt::black, Qt::transparent, 16);
    scores->hide();
    int Window_L = ButtonsStart_X + Button_L * 3 / 2, Window_H = HEADDISTANCE + VERTICALNUM * (VERTICALUNITNUM * VERTICALSIDELENGTH + VERTICALDISTANCE);
    resize(Window_L, Window_H);

    QObject::connect(newStart, &MPushButton::clicked, [=](){
        rounds->show();
        scores->show();
        atMid->setText("VS");
        newGame->show();
        this->game->restart(0);
        this->update();
    });
    QObject::connect(newGame, &MPushButton::clicked, [=](){
        int n = 0;
        if(game->score[0] >= game->score[1]) n = 1;
        else n = 0;
        this->game->resetGameState(n);
        this->update();
    });
}

ChessGameWindow::~ChessGameWindow()
{
    if (exit != nullptr) delete exit;
    if (newStart != nullptr) delete newStart;
    if (newGame != nullptr) delete newGame;
    if (atMid != nullptr) delete atMid;
    if (rounds != nullptr) delete rounds;
    if (scores != nullptr) delete scores;
    if (game != nullptr) delete game;
}

void ChessGameWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (game->agent[0] != nullptr and game->agent[1] != nullptr)
    {
        QPoint QP = event->pos();
        tempP = drawer.calculateMousePos(QP);
        update();
    }
}
