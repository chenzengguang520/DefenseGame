#pragma once

#include <QMainWindow>
#include "ui_Pass1.h"
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include "Defense.h"
#include "DefenseTower.h"
#include <QVBoxLayout>

class Pass1 : public QMainWindow
{
	Q_OBJECT

public:
	Pass1(QWidget *parent = nullptr);
	~Pass1();

	void paintEvent(QPaintEvent* event);


private:
	Ui::Pass1Class ui;

signals:
	void handleTowerDropped();
};



