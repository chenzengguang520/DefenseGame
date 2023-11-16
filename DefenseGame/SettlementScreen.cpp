#include "SettlementScreen.h"

SettlementScreen::SettlementScreen(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

SettlementScreen::~SettlementScreen()
{}


void SettlementScreen::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QPixmap pixmap("./images/failed.jpg");
	painter.drawPixmap(this->rect(), pixmap);
	this->resize(1024, 568);
}