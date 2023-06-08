#include "MainWindow.h"
#include "NineNineWindow.h"

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

    QObject::connect(mainW->nineNineEnter, &QPushButton::clicked, [=]() {
        stackedW->resize(800, 700);
        stackedW->setWindowTitle("NineNine");
        stackedW->setCurrentIndex(1);
        nineNineW->update();
        }); 
    QObject::connect(nineNineW->exit, &QPushButton::clicked, [=]() {
        stackedW->resize(500, 400);
        stackedW->setWindowTitle("Chess Games");
        stackedW->setCurrentIndex(0);
        });
    QObject::connect(nineNineW->game, &ChessGame::agentsCreated, stackedW, &QStackedWidget::show);
    QObject::connect(nineNineW->newStart, &QPushButton::clicked, stackedW, &QStackedWidget::hide);
    QObject::connect(mainW->exit, &QPushButton::clicked, [=]() {
        delete mainW;
        delete nineNineW;
        delete stackedW;
        });

    return a.exec();
}