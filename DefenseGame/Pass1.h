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
#include <cmath>

class Pass1 : public QMainWindow
{
	Q_OBJECT

public:
	Pass1(QWidget *parent = nullptr);
	~Pass1();

	void paintEvent(QPaintEvent* event);
	void paintTower(int id,int x,int y);
	void mousePressEvent(QMouseEvent* event);
	void updateDistance();
public:
	QVector<QPoint>acPos;
	QVector<bool> canMove;
	QVector<QPoint>enemyPos;
	QVector<Defense*>defenses;
	QVector<QVector<double>>distances;//tower i to enemy distance



private:
	Ui::Pass1Class ui;
	QPair<double,double> getGap(double x, double y,double v);

protected:
	//void mousePressEvent(QMouseEvent* event);

signals:
	void handleTowerDropped();

public :
	void receiveId(int data);
	void enemyMove(Enemy* enemy,int index);

	double getDistance(double x1, double y1, double x2, double y2);

private:
	int defenseId = -1;
	bool isMoved = false;
	bool isPressed = false;
	QSet<QPair<int, int>>posSet;
	
	
	int time = 0;
	int enemyId = 0;
	QVector<Enemy*> enemys;
	int moveId = 0;
	bool makeEnemy = false;


	int num = 2;//有多少个炮塔
	int enemyNum = 10;//有多少个怪

	const int MAX_NUM = 0X7fffffff;

	QVector<bool> isAttack;//第i个炮塔正在攻击

	QMap<int, int>attackObject; // 第几号防御塔攻击第几号对线

};



