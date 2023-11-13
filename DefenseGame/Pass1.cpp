#include "Pass1.h"


Pass1::Pass1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);


	this->installEventFilter(this);


	DefenseTower* ac = new DefenseTower(this);
	ac->move(QPoint(this->width() / 2, this->height() / 2));
	QPair<double, double>position (this->width() * 1.0 / 2, this->height() * 1.0 / 2);
	qDebug() << " xx = " << this->width() * 1.0 / 2 << " yy = " << this->height() * 1.0 / 2;
	ac->show();


	this->resize(1024, 568);
	QPoint q(0, 0);

	Defense* defense = new Defense("./images/Fortress/small1.BMP", this);
	defense->setParent(this);
	defense->show();


	Defense* defense1 = new Defense(this,"./images/Fortress/small1.BMP",q);

	defense1->setParent(this);
	defense1->show();
	defense1->setPosition(position);

	connect(defense1, &Defense::clicked, this, [=]() {

		defenseId = defense1->positionId;
		qDebug() << "defenseID = " << defenseId;

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
