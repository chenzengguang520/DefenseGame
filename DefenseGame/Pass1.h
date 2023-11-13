#pragma once

#include <QMainWindow>
#include "ui_Pass1.h"
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include "Defense.h"
#include "DefenseTower.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include "Enemy.h"
#include <QTimer>

class Pass1 : public QMainWindow
{
	Q_OBJECT

public:
	Pass1(QWidget *parent = nullptr);
	~Pass1();

	void paintEvent(QPaintEvent* event);
	void paintTower(int id,int x,int y);

public:
	QVector<QPoint>acPos;
	QVector<bool> canMove;
	QVector<QPoint>enemyPos;


private:
	Ui::Pass1Class ui;
	QPair<double,double> getGap(double x, double y,double v);

protected:
	//void mousePressEvent(QMouseEvent* event);

signals:
	void handleTowerDropped();

public slots:
	void receiveId(int data);

private:
	int defenseId = -1;
	bool isMoved = false;
	bool isPressed = false;
	QSet<QPair<int, int>>posSet;
	int enemyMinNum = 1;
	int enemyMaxNum = 13;
	double initx = 0;
	double inity = 0;
	double destinationX = 0;
	double destinationY = 0;
	double dx = 0;
	double dy = 0;
	int enemyPosId = 0;

};



