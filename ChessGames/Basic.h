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
    //�����Ƿǳ�ͨ�õ�
public:
    void set(int HEADDISTANCE = 100,//���̵���������
        int SIDEDISTANCE = 50, //���̵���߾���
        int VERTICALNUM = 3,//��ֱ����С���̸���
        int HORIZONTALNUM = 3,//ˮƽ����С���̸���
        int VERTICALDISTANCE = 50,//��ֱ����С���̼��
        int HORIZONTALDISTANCE = 50,//ˮƽ����С���̼��
        int VERTICALUNITNUM = 3,//��ֱ����С���̵�Ԫ�����
        int HORIZONTALUNITNUM = 3,//ˮƽ����С���̵�Ԫ�����
        int VERTICALSIDELENGTH = 50,//��ֱ����С���̵�Ԫ��߳�
        int HORIZONTALSIDELENGTH = 50,//ˮƽ����С���̵�Ԫ��߳�
        int SIDEWIDTH = 2,//С���̱߿��ߴ�ϸ
        int INSIDEWIDTH = 1);//С�����ڲ��ߴ�ϸ
    void drawSmallBoard(const int which, const QColor color, QWidget* parent);
    QPoint calculateMousePos(QPoint pos);
    void drawItem(const int skin, const QColor color, QWidget* parent, const QPoint p);

    int headdistance = 0;//���̵���������
    int sidedistance = 0;//���̵���߾���

    int verticalnum = 0;//��ֱ����С���̸���
    int horizontalnum = 0;//ˮƽ����С���̸���
    int verticaldistance = 0;//��ֱ����С���̼��
    int horizontaldistance = 0;//ˮƽ����С���̼��

    int verticalunitnum = 0;//��ֱ����С���̵�Ԫ�����
    int horizontalunitnum = 0;//ˮƽ����С���̵�Ԫ�����
    int verticalsidelength = 0;//��ֱ����С���̵�Ԫ��߳�
    int horizontalsidelength = 0;//ˮƽ����С���̵�Ԫ��߳�

    int sidewidth = 0;//С���̱߿��ߴ�ϸ
    int insidewidth = 0;//С�����ڲ��ߴ�ϸ
};

#endif //BASIC_H
