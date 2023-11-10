#include "Pass1.h"
#include<QPainter>

Pass1::Pass1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->resize(1024, 568);


}

Pass1::~Pass1()
{}


void Pass1::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QPixmap pixmap("./images/maps/bg.bmp");
	painter.drawPixmap(this->rect(), pixmap);
}