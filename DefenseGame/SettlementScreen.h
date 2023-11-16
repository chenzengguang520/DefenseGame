#pragma once

#include <QMainWindow>
#include "ui_SettlementScreen.h"
#include <QPainter>

class SettlementScreen : public QMainWindow
{
	Q_OBJECT

public:
	SettlementScreen(QWidget *parent = nullptr);
	~SettlementScreen();

	void paintEvent(QPaintEvent* event);

private:
	Ui::SettlementScreenClass ui;
};
