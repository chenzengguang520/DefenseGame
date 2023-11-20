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
	int blood = 1000;		
	int speed = 0;
	int id = 0;
	QString enemyPath = "";
	QPair<double, double>position;
	bool isChange = false;
	double initx = 0;
	double inity = 0;
	double destinationX = 0;
	double destinationY = 0;
	double dx = 0;
	double dy = 0;
	int enemyPosId = 0;
	int enemyMinNum = 1;
	int enemyMaxNum = 13;
	bool canMove = false;

};

