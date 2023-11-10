#pragma once

#include <QObject>

class Enemy  : public QObject
{
	Q_OBJECT

public:
	Enemy(QObject *parent);
	~Enemy();
	Enemy();
	Enemy(int b, int s, int d);

	void move(int x, int y, int endX, int endY);

public:
	int blood = 0;
	int speed = 0;
	int id = 0;
};

