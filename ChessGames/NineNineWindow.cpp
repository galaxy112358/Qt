#include "NineNineWindow.h"

NineNineWindow::NineNineWindow(QWidget *parent) : ChessGameWindow(parent, 100, 50, 3, 3, 50, 50, 3, 3, 50, 50, 2, 1)
{
	tempP.rx() = -1; tempP.ry() = -1;
    game = new NineNineGame;
}

NineNineWindow::~NineNineWindow()
{
    if (exit != nullptr) delete exit;
    if (newStart != nullptr) delete newStart;
    if (newGame != nullptr) delete newGame;
    if (atMid != nullptr) delete atMid;
    if (rounds != nullptr) delete rounds;
    if (scores != nullptr) delete scores;
    if (game != nullptr) delete game;
}

void NineNineWindow::paintEvent(QPaintEvent* event)
{
	if (game == nullptr)
		for (int i = 0; i < 9; i++)
			drawer.drawSmallBoard(i, Qt::gray, this);
	else
	{
		for (int i = 0; i < 9; i++)
        {
            if (((NineNineGame*)game)->occupy[i] == 3) drawer.drawSmallBoard(i, Qt::darkGray, this);
            else if (((NineNineGame*)game)->occupy[i] == 1 or ((NineNineGame*)game)->occupy[i] == 2) drawer.drawSmallBoard(i, ((NineNineGame*)game)->agent[((NineNineGame*)game)->occupy[i] - 1]->color, this);
            else if (((NineNineGame*)game)->available[i]) drawer.drawSmallBoard(i, Qt::gray, this);
			else drawer.drawSmallBoard(i, Qt::lightGray, this);
		}
		for(int i = 0; i < 9; i++)
			for(int j = 0; j < 9; j++)
                if (((NineNineGame*)game)->board[i][j])
				{
					QPoint p(i, j);
                    if (((NineNineGame*)game)->occupy[i]==3)
                        drawer.drawItem(((NineNineGame*)game)->agent[((NineNineGame*)game)->board[i][j] - 1]->skin, Qt::darkGray, this, p);
                    else if(((NineNineGame*)game)->occupy[i])
                        drawer.drawItem(((NineNineGame*)game)->agent[((NineNineGame*)game)->board[i][j] - 1]->skin, ((NineNineGame*)game)->agent[((NineNineGame*)game)->occupy[i] - 1]->color, this, p);
                    else drawer.drawItem(((NineNineGame*)game)->agent[((NineNineGame*)game)->board[i][j] - 1]->skin, ((NineNineGame*)game)->agent[((NineNineGame*)game)->board[i][j] - 1]->color, this, p);
				}
		if (tempP.x() != -1 and tempP.y() != -1)
		{
			POINT P;
			P.x = tempP.x(); P.y = tempP.y();
            if (((NineNineGame*)game)->judgeLegal(P))
                drawer.drawItem(((NineNineGame*)game)->agent[((NineNineGame*)game)->turn]->skin, ((NineNineGame*)game)->agent[((NineNineGame*)game)->turn]->color, this, tempP);
		}

        QString s1 = "Round " + QString((std::to_string(game->total + 1)).c_str());
        rounds->setText(s1);
        QString s2 = "Scores  " + QString((std::to_string(game->score[0])).c_str()) + " : " + QString((std::to_string(game->score[1])).c_str());
        scores->setText(s2);

		if (game->agent[0] != nullptr)
        {
            game->agent[0]->info->setParent(this);
            QPoint p = atMid->pos();
            QSize s = atMid->size();
            game->agent[0]->info->setGeometry(p.x() + s.width() / 2 - 250, p.y(), 200, s.height());
            QPalette palette = game->agent[0]->info->palette();
			if (game->turn == 0)
				palette.setColor(QPalette::WindowText, game->agent[0]->color);
			else 
                palette.setColor(QPalette::WindowText, Qt::darkGray);
            game->agent[0]->info->setPalette(palette);
            game->agent[0]->info->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            game->agent[0]->info->show();
		}
		if (game->agent[1] != nullptr)
		{
            game->agent[1]->info->setParent(this);
            QPoint p = atMid->pos();
            QSize s = atMid->size();
            game->agent[1]->info->setGeometry(p.x() + s.width() / 2 + 50, p.y(), 200, s.height());
            QPalette palette = game->agent[1]->info->palette();
            if (game->turn == 1)
                palette.setColor(QPalette::WindowText, game->agent[1]->color);
            else
                palette.setColor(QPalette::WindowText, Qt::darkGray);
            game->agent[1]->info->setPalette(palette);
            game->agent[1]->info->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            game->agent[1]->info->show();
		}
	}
}

void NineNineWindow::mousePressEvent(QMouseEvent* event)
{
	if (game->agent[0] != nullptr and game->agent[1] != nullptr)
	{
		QPoint QP = event->pos();
		QP = drawer.calculateMousePos(QP);
		POINT P;
		P.x = QP.x(); P.y = QP.y();
		if (P.x != -1 and P.y != -1)
		{
			if (game->judgeLegal(P))
			{
				game->changeGameState(P);
				if (game->judgeEnd())
				{
					int x = game->judgeEnd();
					for (int i = 0; i < 9; i++)
                        ((NineNineGame*)game)->available[i] = 0;
					if (x == 1 or x == 2) game->score[x - 1]++;
					game->total++;
				}
				update();
			}
		}
	}
}
