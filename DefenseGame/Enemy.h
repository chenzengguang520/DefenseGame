#pragma once

#include <QObject>
#include <QPushButton>

class Enemy  : public QPushButton
{
	Q_OBJECT

public:
	~Enemy();
	Enemy(QString path);
	Enemy(int b, int s, int d);
	void changShape(QString path);

public:
	int blood = 0;
	int speed = 0;
	int id = 0;
};

