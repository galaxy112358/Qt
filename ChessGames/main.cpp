#include "MainWindow.h"
#include "NineNineWindow.h"
#include "ReversiWindow.h"
#include "GoBangWindow.h"
#include "NineGridWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStackedWidget* stackedW = new QStackedWidget;
    stackedW->resize(500, 400);
    stackedW->setWindowTitle("Chess Games");
    stackedW->setCurrentIndex(0);
    stackedW->move(450, 100);
    stackedW->show();

    MainWindow* mainW = new MainWindow;
    stackedW->addWidget(mainW);

    NineNineWindow* nineNineW = new NineNineWindow;
    stackedW->addWidget(nineNineW);

    ReversiWindow* reversiW = new ReversiWindow;
    stackedW->addWidget(reversiW);

    GoBangWindow* goBangW = new GoBangWindow;
    stackedW->addWidget(goBangW);

    NineGridWindow* nineGridW = new NineGridWindow;
    stackedW->addWidget(nineGridW);

    QObject::connect(mainW->nineNineEnter, &QPushButton::clicked, [=]() {
        stackedW->resize(800, 700);
        stackedW->setWindowTitle("NineNine");
        stackedW->setCurrentIndex(1);
        nineNineW->update();
        });
    QObject::connect(mainW->reversiEnter, &QPushButton::clicked, [=]() {
        stackedW->resize(650, 550);
        stackedW->setWindowTitle("Reversi");
        stackedW->setCurrentIndex(2);
        reversiW->update();
    });
    QObject::connect(mainW->goBangEnter, &QPushButton::clicked, [=]() {
        stackedW->resize(850, 750);
        stackedW->setWindowTitle("GoBang");
        stackedW->setCurrentIndex(3);
        goBangW->update();
    });
    QObject::connect(mainW->nineGridEnter, &QPushButton::clicked, [=]() {
        stackedW->resize(700, 500);
        stackedW->setWindowTitle("NineGrid");
        stackedW->setCurrentIndex(4);
        goBangW->update();
    });
    QObject::connect(nineNineW->exit, &QPushButton::clicked, [=]() {
        stackedW->resize(500, 400);
        stackedW->setWindowTitle("Chess Games");
        stackedW->setCurrentIndex(0);
        });
    QObject::connect(reversiW->exit, &QPushButton::clicked, [=]() {
        stackedW->resize(500, 400);
        stackedW->setWindowTitle("Chess Games");
        stackedW->setCurrentIndex(0);
    });
    QObject::connect(goBangW->exit, &QPushButton::clicked, [=]() {
        stackedW->resize(500, 400);
        stackedW->setWindowTitle("Chess Games");
        stackedW->setCurrentIndex(0);
    });
    QObject::connect(nineGridW->exit, &QPushButton::clicked, [=]() {
        stackedW->resize(500, 400);
        stackedW->setWindowTitle("Chess Games");
        stackedW->setCurrentIndex(0);
    });
    QObject::connect(nineNineW->game, &ChessGame::agentsCreated, stackedW, &QStackedWidget::show);
    QObject::connect(nineNineW->newStart, &QPushButton::clicked, stackedW, &QStackedWidget::hide);
    QObject::connect(reversiW->game, &ChessGame::agentsCreated, stackedW, &QStackedWidget::show);
    QObject::connect(reversiW->newStart, &QPushButton::clicked, stackedW, &QStackedWidget::hide);
    QObject::connect(goBangW->game, &ChessGame::agentsCreated, stackedW, &QStackedWidget::show);
    QObject::connect(goBangW->newStart, &QPushButton::clicked, stackedW, &QStackedWidget::hide);
    QObject::connect(nineGridW->game, &ChessGame::agentsCreated, stackedW, &QStackedWidget::show);
    QObject::connect(nineGridW->newStart, &QPushButton::clicked, stackedW, &QStackedWidget::hide);

    QObject::connect(mainW->exit, &QPushButton::clicked, [=]() {
        delete mainW;
        delete nineNineW;
        delete stackedW;
        });

    return a.exec();
}
