#pragma once

#include "ChessGameWindow.h"
#include "NineNineGame.h"

class NineNineWindow  : public ChessGameWindow
{
	Q_OBJECT

public:
	NineNineWindow(QWidget *parent = nullptr);
	~NineNineWindow();

	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent* event);
};
