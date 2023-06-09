#include "GoBangWindow.h"

GoBangWindow::GoBangWindow(QWidget *parent) : ChessGameWindow(parent, 100, 50, 1, 1, 50, 50, 15, 15, 40, 40, 2, 1)
{
    ended = 0;
    tempP.rx() = -1; tempP.ry() = -1;
    game = new GoBangGame;
    QObject::connect(newStart, &QPushButton::clicked,[&](){ended = 0;});
    QObject::connect(newGame, &QPushButton::clicked,[&](){ended = 0;});
}

GoBangWindow::~GoBangWindow()
{
    if (exit != nullptr) delete exit;
    if (newStart != nullptr) delete newStart;
    if (newGame != nullptr) delete newGame;
    if (atMid != nullptr) delete atMid;
    if (rounds != nullptr) delete rounds;
    if (scores != nullptr) delete scores;
    if (game != nullptr) delete game;
}

void GoBangWindow::paintEvent(QPaintEvent* event)
{
    if (game == nullptr)
        drawer.drawSmallBoard(0, Qt::gray, this);
    else
    {
        drawer.drawSmallBoard(0, Qt::gray, this);
        for(int i = 0; i < 15; i++)
            for(int j = 0; j < 15; j++)
                if(((GoBangGame*)game)->board[i][j] != 0)
                    drawer.drawItem(((GoBangGame*)game)->agent[((GoBangGame*)game)->board[i][j] - 1]->skin, ((GoBangGame*)game)->agent[((GoBangGame*)game)->board[i][j] - 1]->color, this, QPoint(0, i * 15 + j));

        POINT p;
        p.x = tempP.x(), p.y = tempP.y();
        if(!ended and game->judgeLegal(p))
            drawer.drawItem(((GoBangGame*)game)->agent[((GoBangGame*)game)->turn]->skin, ((GoBangGame*)game)->agent[((GoBangGame*)game)->turn]->color, this, tempP);
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

void GoBangWindow::mousePressEvent(QMouseEvent* event)
{
    if(ended == 1) return;
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
                int x = game->judgeEnd();
                if (x)
                {
                    drawer.drawSmallBoard(0,Qt::darkGray,this);
                    if (x == 1 or x == 2) game->score[x - 1]++;
                    game->total++;
                    ended = 1;
                }
                update();
            }
        }
    }
}
