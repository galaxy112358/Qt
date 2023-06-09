#pragma once

#include "Basic.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    MLabel* welcomeWord;
    MPushButton* nineNineEnter, * reversiEnter, * goBangEnter, * nineGridEnter, * exit;

};
