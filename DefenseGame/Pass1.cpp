﻿#include "Pass1.h"


Pass1::Pass1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);


	this->installEventFilter(this);

	qDebug() << "this->x = " << this->width() << " this->y = " << this->height();


	QPoint p1(this->width() / 2, this->height() / 2);
	QPoint p2(this->width() * 0.8, this->height() * 0.8);

	acPos.push_back(p1);
	acPos.push_back(p2);

	for (const auto& cur : acPos)
	{
		DefenseTower* ac = new DefenseTower(this);
		ac->move(cur);
		qDebug() << " xx = " << this->width() * 1.0 / 2 << " yy = " << this->height() * 1.0 / 2;
		ac->show();
	}

	this->resize(1024, 568);
	QPoint q(0, 0);

	Defense* defense11 = new Defense("./images/Fortress/small1.BMP", this);
	defense11->setParent(this);
	defense11->show();

	Defense* defense12 = new Defense("./images/Fortress/small2.BMP", this);
	defense12->setParent(this);
	defense12->move(defense11->size().width() + 5, 0);
	defense12->show();


	int num = 2;
	Defense* defense1 = new Defense(this,"./images/Fortress/small1.BMP",q,num);

	defense1->setParent(this);
	defense1->show();
	
	Defense* defense2 = new Defense(this, "./images/Fortress/small2.BMP", q, num);
	defense2->setParent(this);
	defense2->move(defense1->size().width() + 5,0);
	defense2->initPos = defense2->pos();
	defense2->show();
	int count = 0;
	for (auto& cur : acPos)
	{
		int posx = cur.x();
		int posy = cur.y();
		qDebug() << "count = " << count << " posx = " << posx << " posy = " << posy;
		QPair<int, int>position(posx,posy);
		defense1->setPosition(position);
		defense2->setPosition(position);
		defense1->towers[count]->move(posx, posy);
		defense1->towers[count]->setParent(this);
		defense1->towers[count]->hide();
		defense2->towers[count]->move(posx, posy);
		defense2->towers[count]->setParent(this);
		defense2->towers[count++]->hide();

	}

	//gogogo
	Enemy* enemy = new Enemy("./images/monster1/down_1.BMP");
	enemy->setParent(this);
	enemy->move(this->width() * 0.45, 0);
	enemyPos.push_back(QPoint(450, 0));
	enemyPos.push_back(QPoint(450, 105));
	enemyPos.push_back(QPoint(400, 165));
	enemyPos.push_back(QPoint(250, 200));
	enemyPos.push_back(QPoint(245, 250));
	enemyPos.push_back(QPoint(240, 300));
	enemyPos.push_back(QPoint(280, 350));
	enemyPos.push_back(QPoint(300, 350));
	enemyPos.push_back(QPoint(400, 350));
	enemyPos.push_back(QPoint(500, 350));
	enemyPos.push_back(QPoint(600, 350));

	QTimer* timer = new QTimer;

	timer->start(50);
	initx = enemyPos[0].x();
	inity = enemyPos[0].y();
	destinationX = enemyPos[1].x();
	destinationY = enemyPos[1].y();
	dy = 1;
	enemyPosId++;
	connect(timer, &QTimer::timeout, [=]() {

		QString enemyPath = QString(QString("./images/monster1/down_%1.BMP").arg(enemyMinNum++));
		enemy->changShape(enemyPath);
		initx += dx;
		inity += dy;
		qDebug() << "inity = " << inity<<" initx = "<<initx;
		enemy->move(initx, inity);
		//qDebug() << "inity = " << inity;
// 		if (inity == 50)
// 		{
// 			qDebug() << "initx = " << initx;
// 			timer->stop();
// 		}
		if (inity - destinationY <= 1 && inity - destinationY >= -1 && initx - destinationX <= 1 && initx - destinationX >= -1)
		{
/*			dx = -1;*/
			initx = destinationX;
			inity = destinationY;
			destinationX = enemyPos[++enemyPosId].x();
			destinationY = enemyPos[enemyPosId].y();
			double X = destinationX - initx;
			double Y = destinationY - inity;
			QPair<double, double> v = getGap(destinationX - initx, destinationY - inity,1.0);
			dx = v.first;
			dy = v.second;
		}
		if (enemyMinNum + 1 > enemyMaxNum)
		{
			enemyMinNum = 1;
		}
	});


}

Pass1::~Pass1()
{}


void Pass1::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QPixmap pixmap("./images/maps/bg.bmp");
	painter.drawPixmap(this->rect(), pixmap);
}

void Pass1::receiveId(int data)
{
	// 处理接收到的数据
	qDebug() << "Received data in pass1:" << data;
	defenseId = data;
}



void Pass1::paintTower(int id, int x, int y)
{

}

QPair<double,double> Pass1::getGap(double x, double y,double V)
{
	double tana = y * V * 0.1 / x;
	tana = tana > 0 ? tana : -1 * tana;
	qDebug() << "tana = " << tana;
	double vx = 1.0 / sqrt(1 + tana);
	double vy = 1.0 / sqrt(1 + tana) * tana;
	vx = x > 0 ? vx : -1 * vx;
	vy = y > 0 ? vy : -1 * vy;
	return QPair<double, double>(vx, vy);
}
