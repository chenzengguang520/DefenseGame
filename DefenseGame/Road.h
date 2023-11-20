#pragma once

#include <QMainWindow>
#include "ui_Road.h"

class Road : public QMainWindow
{
	Q_OBJECT

public:
	Road(QWidget *parent = nullptr);
	~Road();

private:
	Ui::RoadClass ui;
};
