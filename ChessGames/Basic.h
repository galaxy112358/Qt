#pragma once
#ifndef BASIC_H
#define BASIC_H

#include <Windows.h>
#include <thread>
#include <ctime>
#include <chrono>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWizard>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QColor>
#include <QtCore/QStringList>
#include <QtCore/QString>
#include <QtCore/QDebug>

#pragma comment(lib,"ws2_32.lib")

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define FontColor  QColor(241, 192, 5)
#define BackColor QColor(76, 243, 255, 100)
#define DefaultRect QRect(0, 0, 50, 50)

QString currentTime();

int randomNum(int x = 1);

class MLabel :public QLabel
{
public:
    MLabel(QWidget* parent = nullptr, QRect Geo = DefaultRect, int border_radius = 0, QColor color = FontColor, QColor bkColor = Qt::transparent, int px = 12, QString font = "Times New Roman", int method = 0);
};

class MPushButton :public QPushButton
{
public:
    MPushButton(QWidget* parent = nullptr, QRect Geo = DefaultRect, int border_radius = 0, QColor color = FontColor, QColor bkColor = BackColor, int px = 12, QString font = "Times New Roman", int method = 0);
};

class BoardDrawer {
    //该类是非常通用的
public:
    void set(int HEADDISTANCE = 100,//棋盘到顶部距离
        int SIDEDISTANCE = 50, //棋盘到左边距离
        int VERTICALNUM = 3,//竖直方向小棋盘个数
        int HORIZONTALNUM = 3,//水平方向小棋盘个数
        int VERTICALDISTANCE = 50,//竖直方向小棋盘间隔
        int HORIZONTALDISTANCE = 50,//水平方向小棋盘间隔
        int VERTICALUNITNUM = 3,//竖直方向小棋盘单元格个数
        int HORIZONTALUNITNUM = 3,//水平方向小棋盘单元格个数
        int VERTICALSIDELENGTH = 50,//竖直方向小棋盘单元格边长
        int HORIZONTALSIDELENGTH = 50,//水平方向小棋盘单元格边长
        int SIDEWIDTH = 2,//小棋盘边框线粗细
        int INSIDEWIDTH = 1);//小棋盘内部线粗细
    void drawSmallBoard(const int which, const QColor color, QWidget* parent);
    QPoint calculateMousePos(QPoint pos);
    void drawItem(const int skin, const QColor color, QWidget* parent, const QPoint p);

    int headdistance = 0;//棋盘到顶部距离
    int sidedistance = 0;//棋盘到左边距离

    int verticalnum = 0;//竖直方向小棋盘个数
    int horizontalnum = 0;//水平方向小棋盘个数
    int verticaldistance = 0;//竖直方向小棋盘间隔
    int horizontaldistance = 0;//水平方向小棋盘间隔

    int verticalunitnum = 0;//竖直方向小棋盘单元格个数
    int horizontalunitnum = 0;//水平方向小棋盘单元格个数
    int verticalsidelength = 0;//竖直方向小棋盘单元格边长
    int horizontalsidelength = 0;//水平方向小棋盘单元格边长

    int sidewidth = 0;//小棋盘边框线粗细
    int insidewidth = 0;//小棋盘内部线粗细
};

#endif //BASIC_H
