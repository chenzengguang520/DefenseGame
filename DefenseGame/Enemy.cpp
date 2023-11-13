#include "Enemy.h"



Enemy::~Enemy()
{}

Enemy::Enemy(QString path)
{
	changShape(path);

}

Enemy::Enemy(int b, int s, int d)
{
	this->blood = b;
	this->speed = s;
	this->id = d;
}

void Enemy::changShape(QString path)
{
	QPixmap originalPixmap;
	bool ret = originalPixmap.load(path);
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


