#include "ChessGame.h"

QString TPName[1] = { "Player" };

//ChessAgent
ChessAgent::ChessAgent(QString TYPENAME, QPoint p)
{
	name = "unknown";
	type = 0;
	color = Qt::lightGray;
	skin = 1;

	QWidget* w = new QWidget;

	MLabel* ty = new MLabel(w, QRect(75, 25, 150, 50), 5);
	ty->setText(TYPENAME);

	MPushButton* choose1 = new MPushButton(w, QRect(75, 100, 150, 50), 5);
	choose1->setText("Choose Agent");

	MPushButton* choose2 = new MPushButton(w, QRect(75, 200, 150, 50), 5);
	choose2->hide();
	choose2->setText("Type Name");

	MPushButton* choose3 = new MPushButton(w, QRect(75, 300, 150, 50), 5);
	choose3->hide();
	choose3->setText("Choose Skin");

	MPushButton* choose4 = new MPushButton(w, QRect(75, 400, 150, 50), 5);
	choose4->hide();
    choose4->setText("Choose Color");

    MPushButton* de = new MPushButton(w, QRect(75, 400, 150, 50), 5);
    de->setText("Default Settings");

	QObject::connect(choose1, &QPushButton::clicked, [=]()
		{
			while (1)
			{
				QStringList items;
				items << "Player";
				bool ok;
				QString item = QInputDialog::getItem(w, "Choose Agent", "Type:", items, 0, false, &ok);
				if (ok && !item.isEmpty())
					if (item == "Player")
					{
						type = 0;
						choose1->setText(item);
						choose2->show();
                        de->hide();
						break;
					}
			}
		});
	QObject::connect(choose2, &QPushButton::clicked, [=]()
		{
            while(1)
            {
                name = QInputDialog::getText(w, "Type Your Name", "Your Name(Within 8 letters):");
                if(!name.isEmpty() and name.length() <= 8) break;
            }
			choose2->setText(name);
			choose3->show();
		});
	QObject::connect(choose3, &QPushButton::clicked, [=]()
		{
			while (1)
			{
				QStringList items;
				items << "Solid Circle" << "Hollow Circle";
				bool ok;
				QString item = QInputDialog::getItem(w, "Choose Skin", "Type:", items, 0, false, &ok);
				if (ok && !item.isEmpty())
					if (item == "Solid Circle")
					{
						skin = 1;
						choose3->setText(item);
						break;
					}
					else if (item == "Hollow Circle")
					{
						skin = 2;
						choose3->setText(item);
						break;
					}
			}
			choose4->show();
		});
	QObject::connect(choose4, &QPushButton::clicked, [=]()
		{
            while(1)
            {
                color = QColorDialog::getColor(Qt::black, w, "Choose Color");
                if(color.isValid()) break;
            }
            choose4->setText("Color chosen");

            info = new MLabel(nullptr, DefaultRect, 0, color, Qt::transparent, 16);
            QString s = TPName[type] + " " + name;
            info->setText(s);
            info->hide();
			emit agentCreated();
			delete ty;
			delete choose1;
			delete choose2;
			delete choose3;
			delete choose4;
            delete de;
			delete w;
		});
    QObject::connect(de, &QPushButton::clicked, [=](){
        type = 0;
        name = "default";
        int r1 = randomNum(2), r2 = randomNum(3), r3 = randomNum(5), r4 = randomNum(7);
        skin = r1 % 2 + 1;
        color = QColor(r1 % 256, r2 % 256, r3 % 256, r4 % 256);
        info = new MLabel(nullptr, DefaultRect, 0, color, Qt::transparent, 16);
        QString s = TPName[type] + " " + name;
        info->setText(s);
        info->hide();
        emit agentCreated();
        delete ty;
        delete choose1;
        delete choose2;
        delete choose3;
        delete choose4;
        delete de;
        delete w;
    });

	w->setWindowTitle(TYPENAME);
	w->resize(300, 500);
	w->show();
	w->move(p);
}

ChessAgent::~ChessAgent()
{
    if(info != nullptr) delete info;
}

//ChessGame
ChessGame::~ChessGame()
{
    if(agent[0] != nullptr) delete agent[0];
    if(agent[1] != nullptr) delete agent[1];
}
