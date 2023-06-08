#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->resize(500, 400);

    //欢迎语标签
    welcomeWord = new MLabel(this, QRect(100, 50, 300, 50), 5, FontColor, Qt::transparent, 16);
    welcomeWord->setText("Welcome to chess games !");

    //退出按钮
    exit = new MPushButton(this, QRect(300, 300, 100, 35), 5);
    exit->setText("Exit");

    //NineNine游戏进入按钮
    nineNineEnter = new MPushButton(this, QRect(50, 125, 100, 35), 5);
    nineNineEnter->setText("NineNine");
}

MainWindow::~MainWindow()
{
    delete welcomeWord;
    delete exit;
    delete nineNineEnter;
}
