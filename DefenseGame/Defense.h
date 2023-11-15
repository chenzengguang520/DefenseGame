#pragma once
#ifndef DEFENSE_H
#define DEFENSE_H

#include <QObject>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
#include <QMimeData>
#include <QDrag>
#include <QSet>
#include <QVector>
#include "Bullet.h"

class Defense : public QPushButton
{
    Q_OBJECT

public:
	Defense();
    ~Defense();
    Defense(QWidget* pass1,QString path,QPoint q,int num,int id);
	Defense(QString path,QWidget* parent = nullptr);
    void setMargin(int left, int top, int right, int bottom);
	void setPosition(QPair<double,double> p);
	int check(QEvent* event);
	//void paintTower(int x, int y, int id);
	void makeDefenses(int num);
	bool isShowed();


	void attackAnimation(double x,double y);
	void attackAnimation(Enemy*);
	void changeTower(QString );
	void changeTower(QPixmap& );
	

	void opebFire(double x, double y);

protected:
    bool eventFilter(QObject* watched, QEvent* event);

public:
    QString path;
    QPoint dragStartPosition;
    QPoint originalButtonPosition;
    QPoint moveDelta;
    QTimer* timer = nullptr;
	int positionId = 0;
	QVector<Defense*> towers;
	QPoint initPos;  //记录初始位置
	QVector<QPair<int, int>>positon; //可以放置的位置坐标
	bool isShowing;// 现在是否是显形状态



	double attackRadius;

	int defenseId;
	int shapeId;
	QVector<QPixmap>shapes;


	Bullet* bullet = nullptr;


	QVector<Bullet*> bullets;//弹药库
	int bulletId = 0;

	bool attackEnd = true;




private:
	QWidget* pass1 = nullptr;
	QString text;                   //显示文字
	bool isPressed;                 //鼠标是否按下
	QPoint lastPoint;               //鼠标按下最后坐标
	QString type;                   //图片末尾类型
	QString imgPath;                //背景图片路径
	QString imgName;                //背景图片名称
	int  iconWidth = 0;             //图片宽度
	int iconHeight = 0;              //图片高度
	bool isMoved;                   //是否正在移动中
	int x_left_distance;            //可移动的距离左侧的距离
	int y_top_distance;             //可移动的距离上面的距离
	int x_right_distancce;          //可移动的距离右侧的距离+
	int y_bottom_distance;          //可移动的距离上底部的距离
	bool isChecked = false;          //按钮的选中状态
	bool isShow = false; //判断是否显形过
	bool isCheckAc = false;
	Defense* des = nullptr;
	static QVector<bool> canMove; //防止多个防御塔放到同一个位置

	
	

private slots:


signals:
	void clicked();
	void doubleClicked();
	void toggled(bool isToggled);
public slots:
	void sendDefenseID(int id);
};

#endif // DEFENSE_H
