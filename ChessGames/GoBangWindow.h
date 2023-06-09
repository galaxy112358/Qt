#pragma once

#include "ChessGameWindow.h"
#include "GoBangGame.h"

class GoBangWindow  : public ChessGameWindow
{
    Q_OBJECT

public:
    bool ended;
    GoBangWindow(QWidget *parent = nullptr);
    ~GoBangWindow();

    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
};
