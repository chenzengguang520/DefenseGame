#include "defensetower.h"

DefenseTower::DefenseTower(QWidget* parent)
    : QWidget(parent)
{
    //setFixedSize(50, 50);  // 设置防御塔的大小

    
    bool ret = towerPixmap.load("./images/mark/makeTower.png");
    if (!ret)
        qDebug() << "failed load img";
    scaledPixmap = towerPixmap.scaled(towerPixmap.size() * 0.5);
    this -> setFixedSize(scaledPixmap.size());
}

void DefenseTower::paintEvent(QPaintEvent* event)
{

    QPainter painter(this);
    painter.drawPixmap(0, 0, scaledPixmap);
}



