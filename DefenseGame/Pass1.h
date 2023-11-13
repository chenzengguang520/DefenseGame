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

class Pass1 : public QMainWindow
{
	Q_OBJECT

public:
	Pass1(QWidget *parent = nullptr);
	~Pass1();

	void paintEvent(QPaintEvent* event);
	void paintTower(int id,int x,int y);


private:
	Ui::Pass1Class ui;

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
};



