#pragma once

#include "ChessGameWindow.h"
#include "ReversiGame.h"

class ReversiWindow  : public ChessGameWindow
{
    Q_OBJECT

public:
    ReversiWindow(QWidget *parent = nullptr);
    ~ReversiWindow();

    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
};
