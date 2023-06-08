#pragma once

#include "Basic.h"
#include "ChessGame.h"

class ChessGameWindow  : public QWidget
{
	Q_OBJECT

public:
	ChessGameWindow(QWidget *parent = nullptr, int HEADDISTANCE = 100, int SIDEDISTANCE = 50, int VERTICALNUM = 1, int HORIZONTALNUM = 1, int VERTICALDISTANCE = 50, int HORIZONTALDISTANCE = 50, int VERTICALUNITNUM = 3, int HORIZONTALUNITNUM = 3, int VERTICALSIDELENGTH = 50, int HORIZONTALSIDELENGTH = 50, int SIDEWIDTH = 2, int INSIDEWIDTH = 1);
    ~ChessGameWindow();

    ChessGame* game;

	MPushButton* exit;
	MPushButton* newStart, * newGame;
	MLabel* atMid, * rounds, * scores;
    BoardDrawer drawer;
    QPoint tempP;

    void mouseMoveEvent(QMouseEvent* event);
};
