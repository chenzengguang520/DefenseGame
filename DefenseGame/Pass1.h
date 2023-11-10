#pragma once

#include <QMainWindow>
#include "ui_Pass1.h"

class Pass1 : public QMainWindow
{
	Q_OBJECT

public:
	Pass1(QWidget *parent = nullptr);
	~Pass1();

	void paintEvent(QPaintEvent* event);

private:
	Ui::Pass1Class ui;
};



