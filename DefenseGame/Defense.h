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

class Defense : public QPushButton
{
    Q_OBJECT

public:
    ~Defense();
    Defense(QWidget* pass1,QString path,QPoint q);
	Defense(QString path,QWidget* parent = nullptr);
    void setMargin(int left, int top, int right, int bottom);
	void setPosition(QPair<double,double> p);
	bool check(QEvent* event);
	void paintTower(int x, int y, int id);

protected:
    bool eventFilter(QObject* watched, QEvent* event);

public:
    QString path;
    QPoint dragStartPosition;
    QPoint originalButtonPosition;
    QPoint moveDelta;
    QTimer* timer = nullptr;
	int positionId = 0;

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
	QSet<QPair<double, double>>positon; //可以放置的位置坐标
	QPoint initPos;

private slots:


signals:
	void clicked();
	void doubleClicked();
	void toggled(bool isToggled);
	void defenseId(int id);
public slots:
	void sendDefenseID(int id);
};

#endif // DEFENSE_H
