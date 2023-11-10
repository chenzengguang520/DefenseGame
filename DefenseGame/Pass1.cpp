#include "Pass1.h"


Pass1::Pass1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);


	this->resize(1024, 568);
	QPoint q(0, 0);
	Defense* defense1 = new Defense("./images/Fortress/small1.BMP",q);

	defense1->setParent(this);
	defense1->show();
	
// 	QWidget* centralWidget = new QWidget(this);
// 	setCentralWidget(centralWidget);
// 
// 	QVBoxLayout* layout = new QVBoxLayout(centralWidget);
// 
// 	DefenseTower* defenseTower = new DefenseTower(this);
// 	layout->addWidget(defenseTower);
// 
// 	QWidget* w = new QWidget(this);
// 	w->show();

}

Pass1::~Pass1()
{}


void Pass1::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QPixmap pixmap("./images/maps/bg.bmp");
	painter.drawPixmap(this->rect(), pixmap);
}


