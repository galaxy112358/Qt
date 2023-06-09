#pragma once

#include "ChessGameWindow.h"
#include "NineGridGame.h"

class NineGridWindow  : public ChessGameWindow
{
    Q_OBJECT

public:
    bool ended;
    NineGridWindow(QWidget *parent = nullptr);
    ~NineGridWindow();

    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
};
