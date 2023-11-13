#include "Pass1.h"


Pass1::Pass1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);


	this->installEventFilter(this);


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



	connect(defense1, &Defense::clicked, this, [=]() {

		defenseId = defense1->positionId;

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
