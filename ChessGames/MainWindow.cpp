#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->resize(500, 400);

    //��ӭ���ǩ
    welcomeWord = new MLabel(this, QRect(100, 50, 300, 50), 5, FontColor, Qt::transparent, 16);
    welcomeWord->setText("Welcome to chess games !");

    //�˳���ť
    exit = new MPushButton(this, QRect(300, 300, 100, 35), 5);
    exit->setText("Exit");

    //NineNine��Ϸ���밴ť
    nineNineEnter = new MPushButton(this, QRect(50, 125, 100, 35), 5);
    nineNineEnter->setText("NineNine");

    //Reversi��Ϸ���밴ť
    reversiEnter = new MPushButton(this, QRect(200, 125, 100, 35), 5);
    reversiEnter->setText("Reversi");

    //GoBang��Ϸ���밴ť
    goBangEnter = new MPushButton(this, QRect(350, 125, 100, 35), 5);
    goBangEnter->setText("GoBang");

    //nineGrid��Ϸ���밴ť
    nineGridEnter = new MPushButton(this, QRect(50, 195, 100, 35), 5);
    nineGridEnter->setText("NineGrid");
}

MainWindow::~MainWindow()
{
    delete welcomeWord;
    delete exit;
    delete nineNineEnter;
    delete reversiEnter;
    delete goBangEnter;
    delete nineGridEnter;
}
