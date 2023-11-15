#include "Bullet.h"

Bullet::Bullet(QObject *parent)
	: QPushButton()
{}

Bullet::Bullet(QString path,QObject* parent) : QPushButton()
{

	this->path = path;
	QPixmap originalPixmap;
	bool ret = originalPixmap.load(this->path);
	if (!ret)
		qDebug() << "failed";

	// 定义背景颜色的RGB值，例如绿色
	int red = 34;
	int green = 177;
	int blue = 76;

	// 创建一个副本，将背景颜色转换为透明
	QPixmap modifiedPixmap = originalPixmap;
	modifiedPixmap.setMask(originalPixmap.createMaskFromColor(QColor(red, green, blue)));

	this->setFixedSize(modifiedPixmap.size());
	// 设置按钮样式
	this->setStyleSheet("QPushButton{border:0px}");

	// 设置按钮图标
	this->setIcon(QIcon(modifiedPixmap));
	// 设置图标大小
	this->setIconSize(modifiedPixmap.size());

}

Bullet::~Bullet()
{}

void Bullet::attack(double x, double y)
{
	qDebug()<<"x = "<<x<<" "<<"y = "<<y;
	//qDebug() << "begin attack";

	double DX = x - initX;
	double DY = y - initY;

	QPair<double, double>V = getV(DX, DY);


	double dx = V.first;
	double dy = V.second;
	//qDebug() << "bullet dx = " << dx << " bullet dy = " << dy;

	initX += dx;
	initY += dy;


	QTimer* timer = new QTimer;

	timer->start(1);

	connect(timer, &QTimer::timeout, [=]() {

		//qDebug() << "timer is running";
		this->move(initX, initY);
		initX += dx;
		initY += dy;
		if (initX - x >= -2 && initX - x <= 2 && initY - y >= -2 && initY - y <= 2)
		{
			endAttack = true;
			this->hide();
			timer->stop();
		}
		
	});

	


}


void Bullet::attack(Enemy* enemy)
{

	double x = enemy->initx;
	double y = enemy->inity;
	double DX = enemy->initx - initX;
	double DY = enemy->inity - initY;

	QPair<double, double>V = getV(DX, DY);


	double dx = V.first;
	double dy = V.second;
	//qDebug() << "bullet dx = " << dx << " bullet dy = " << dy;

	initX += dx;
	initY += dy;


	QTimer* timer = new QTimer;

	timer->start(1);

	connect(timer, &QTimer::timeout, [=]() {

		//qDebug() << "timer is running";
		this->move(initX + enemy->width() / 2 + enemy->dx, initY + enemy->dy);
		initX += dx;
		initY += dy;
		if (initX - x >= -2 && initX - x <= 2 && initY - y >= -2 && initY - y <= 2)
		{
			endAttack = true;
			enemy->blood -= 1;
			this->hide();
			timer->stop();
		}

	});


}


QPair<double, double> Bullet::getV(double x, double y)
{
	// 	if (x == 0)
	// 	{
	// 		return QPair<double, double>(0, 1.0);
	// 	}
	double arctan_value = atan(y * 1.0 / x);
	//double tana = y * V / x;
	double tana = tan(arctan_value);
	tana = tana > 0 ? tana : -1 * tana;
	// 	double vx = 1.0 / sqrt(1 + tana);
	// 	double vy = 1.0 / sqrt(1 + tana) * tana;

	double vx = 1 * cos(arctan_value);
	double vy = 1 * sin(arctan_value);

	if (x > 0)
	{
		vx = vx > 0 ? vx : -1 * vx;
	}
	else
	{
		vx = vx < 0 ? vx : -1 * vx;
	}
	if (y > 0)
	{
		vy = vy > 0 ? vy : -1 * vy;
	}
	else
	{
		vy = vy < 0 ? vy : -1 * vy;
	}
	return QPair<double, double>(vx, vy);
}
