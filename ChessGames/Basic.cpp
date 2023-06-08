#include "Basic.h"

QString currentTime()
{
    auto now = std::chrono::system_clock::now();
    time_t now_time = std::chrono::system_clock::to_time_t(now);
    char buffer[1024];
    errno_t err = ctime_s(buffer, sizeof(buffer), &now_time);
    if (err == 0)
        return buffer;
    else
    {
        qDebug()<<"currentTime Error !";
        return QString("error");
    }
}

int randomNum(int x)
{
    //生成随机数
    unsigned seed = 0;
    seed = time(0);
    srand(seed);
    return rand() / x;
}

//MLabel
MLabel::MLabel(QWidget* parent, QRect Geo, int border_radius, QColor color, QColor bkColor, int px, QString font, int method) :QLabel(parent)
{
    this->setAutoFillBackground(true);
    this->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    if (method == 0)
    {
        QPalette palette = this->palette();
        palette.setColor(this->backgroundRole(), bkColor);
        palette.setColor(this->foregroundRole(), color);
        this->setPalette(palette);
        this->setFont(QFont(font, px));
    }
    else
    {
        QString style = QString("QLabel{ color: %1; background - color: %2; border - radius: %3px; font - size: %4px; font - family: %5; }")
                            .arg(color.name(),bkColor.name(),std::to_string(border_radius).c_str(),std::to_string(px).c_str(),font);
        this->setStyleSheet(style);
    }
    this->setGeometry(Geo);
}

//MPushButton
MPushButton::MPushButton(QWidget* parent, QRect Geo, int border_radius, QColor color, QColor bkColor, int px, QString font, int method) :QPushButton(parent)
{
    this->setAutoFillBackground(true);
    if (method == 0)
    {
        QPalette palette = this->palette();
        palette.setColor(this->backgroundRole(), bkColor);
        palette.setColor(this->foregroundRole(), color);
        this->setPalette(palette);
        this->setFont(QFont(font, px));
    }
    else
    {
        QString style = QString("QPushButton{ color: %1; background - color: %2; border - radius: %3px; font - size: %4px; font - family: %5; }")
                            .arg(color.name(),bkColor.name(),std::to_string(border_radius).c_str(),std::to_string(px).c_str(),font);
        this->setStyleSheet(style);
    }
    this->setGeometry(Geo);
}

//Drawer
void BoardDrawer::set(int HEADDISTANCE, int SIDEDISTANCE, int VERTICALNUM, int HORIZONTALNUM, int VERTICALDISTANCE, int HORIZONTALDISTANCE, int VERTICALUNITNUM, int HORIZONTALUNITNUM, int VERTICALSIDELENGTH, int HORIZONTALSIDELENGTH, int SIDEWIDTH, int INSIDEWIDTH)
{
    headdistance = HEADDISTANCE;
    sidedistance = SIDEDISTANCE;

    verticalnum = VERTICALNUM;
    horizontalnum = HORIZONTALNUM;
    verticaldistance = VERTICALDISTANCE;
    horizontaldistance = HORIZONTALDISTANCE;

    verticalunitnum = VERTICALUNITNUM;
    horizontalunitnum = HORIZONTALUNITNUM;
    verticalsidelength = VERTICALSIDELENGTH;
    horizontalsidelength = HORIZONTALSIDELENGTH;

    sidewidth = SIDEWIDTH;
    insidewidth = INSIDEWIDTH;
}

void BoardDrawer::drawSmallBoard(const int which, const QColor color, QWidget* parent)
{
    QPainter painter(parent);
    //打印相应小棋盘框线
    int x = which % horizontalnum, y = which / horizontalnum;//横向第x个，纵向第y个棋盘
    //将x, y变为棋盘左上顶点坐标
    x = sidedistance + (horizontaldistance + horizontalsidelength * horizontalunitnum) * x;
    y = headdistance + (verticaldistance + verticalsidelength * verticalunitnum) * y;
    //利用QPaniter打印
    QPen pen;
    pen.setColor(color);
    pen.setWidth(insidewidth);
    painter.setPen(pen);
    for (int i = 1; i < horizontalunitnum; i++) {
        painter.drawLine(x + horizontalsidelength * i, y, x + horizontalsidelength * i, y + verticalsidelength * verticalunitnum);
        painter.drawLine(x, y + verticalsidelength * i, x + horizontalsidelength * horizontalunitnum, y + verticalsidelength * i);
    }
    pen.setWidth(sidewidth);
    painter.setPen(pen);
    painter.drawRect(x, y, horizontalsidelength * horizontalunitnum, verticalsidelength * verticalunitnum);
}

void BoardDrawer::drawItem(const int skin, const QColor color, QWidget* parent, const QPoint p)
{
    QPainter painter(parent);
    const int x = p.x(), y = p.y();
    int board_x = x % horizontalnum, board_y = x / horizontalnum;
    int item_x = y % horizontalunitnum, item_y = y / horizontalunitnum;
    board_x = sidedistance + (horizontaldistance + horizontalsidelength * horizontalunitnum) * board_x;
    board_y = headdistance + (verticaldistance + verticalsidelength * verticalunitnum) * board_y;
    item_x = board_x + horizontalsidelength * item_x;
    item_y = board_y + verticalsidelength * item_y;
    QPen pen(color);
    pen.setWidth(3);
    QBrush brush(color);
    switch (skin) {
    case 1:
        painter.setBrush(brush);
        painter.setPen(Qt::transparent);
        painter.drawEllipse(item_x + horizontalsidelength / 4, item_y + verticalsidelength / 4, horizontalsidelength / 2, verticalsidelength / 2);
        break;
    case 2:
        painter.setPen(pen);
        painter.setBrush(Qt::transparent);
        painter.drawEllipse(item_x + horizontalsidelength / 4, item_y + verticalsidelength / 4, horizontalsidelength / 2, verticalsidelength / 2);
        break;
    default:
        break;
    }
}

QPoint BoardDrawer::calculateMousePos(QPoint pos)
{
    int pos_x = pos.x(), pos_y = pos.y();
    int x = -1, y = -1;//x为棋盘编号，y为格子编号
    for (int i = 0; i < horizontalnum; i++)
        if (pos_x > sidedistance + (horizontalunitnum * horizontalsidelength + horizontaldistance) * i and
            pos_x < sidedistance + (horizontalunitnum * horizontalsidelength + horizontaldistance) * i + horizontalunitnum * horizontalsidelength)
            for (int j = 0; j < verticalnum; j++)
                if (pos_y > headdistance + (verticalunitnum * verticalsidelength + verticaldistance) * j and
                    pos_y < headdistance + (verticalunitnum * verticalsidelength + verticaldistance) * j + verticalunitnum * verticalsidelength)
                    x = i + horizontalnum * j;

    if (x != -1)
    {
        int board_x = x % horizontalnum, board_y = x / horizontalnum;
        board_x = sidedistance + (horizontaldistance + horizontalsidelength * horizontalunitnum) * board_x;
        board_y = headdistance + (verticaldistance + verticalsidelength * verticalunitnum) * board_y;
        pos_x -= board_x;
        pos_y -= board_y;
        for (int i = 0; i < horizontalunitnum; i++)
            for (int j = 0; j < verticalunitnum; j++)
                if (pos_x > horizontalsidelength * i and pos_x < horizontalsidelength * (i + 1)
                    and pos_y > verticalsidelength * j and pos_y < verticalsidelength * (j + 1))
                    y = i + horizontalunitnum * j;
    }
    return QPoint(x, y);
}
