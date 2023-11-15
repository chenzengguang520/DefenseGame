#pragma once

#include <QObject>
#include <QPushButton>
#include <QTimer>
#include "Enemy.h"


class Bullet  : public QPushButton
{
	Q_OBJECT

public:
	Bullet(QObject *parent);
	Bullet(QString path, QObject* parent);
	~Bullet();
	void attack(double x, double y);
	void attack(Enemy*);
	QPair<double,double> getV(double x, double y);

public:
	double initX = 0;
	double initY = 0;
	bool endAttack = false;
	int damage = 1;

public:
	QString path = "";
};
