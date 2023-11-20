#include "DefenseGame.h"


DefenseGame::DefenseGame(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);




	//游戏界面设置
	this->setFixedSize(1024, 568);
	QPushButton* beginBtn = new QPushButton(this);
	beginBtn->move(this->width() / 2, this->height() - this->height() / 4);
	beginBtn->setText("开始");
	connect(beginBtn, &QPushButton::clicked, this, [=]() {

		this->hide();


		//启动计时器

		//运行玩家操作

		//刷怪

		Pass1* pass1 = new Pass1();
		pass1->show();

			
	});


}

DefenseGame::~DefenseGame()
{}

void DefenseGame::paintEvent(QPaintEvent * ev)
{
	//QPainter painter(this);
	//QPixmap pix;
	//pix.load(":/new/prefix1/images/maps/bg.bmp");
	//painter.drawPixmap(0, 0, this->width(), this->height(), pix);

	QPainter painter(this);
	QPixmap pixmap("./images/maps/bg.bmp");
	painter.drawPixmap(this->rect(), pixmap);

}

