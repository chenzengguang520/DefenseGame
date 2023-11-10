#include "Defense.h"


// Defense::Defense(QObject *parent)
// 	: QObject(parent)
// {}

Defense::~Defense()
{}

Defense::Defense(QString path, QPoint q)
{
    initPos = this->pos();
    isPressed = false;
    isMoved = false;
    lastPoint = QPoint();
    x_left_distance = 0;
    x_right_distancce = 0;
    y_top_distance = 0;
    y_bottom_distance = 0;
    this->installEventFilter(this);


	this->originalButtonPosition = q;
	this->dragStartPosition = q;
	this->moveDelta = QPoint(0, 0);


	this->path = path;
	QPixmap originalPixmap;
	bool ret = originalPixmap.load(path);
	if (!ret)
		qDebug() << "failed";

	// 定义背景颜色的RGB值，例如绿色
	int red = 34;
	int green = 177;
	int blue = 76;

	// 创建一个副本，将背景颜色转换为透明
	QPixmap modifiedPixmap = originalPixmap;
	modifiedPixmap.setMask(originalPixmap.createMaskFromColor(QColor(red, green, blue)));

	this->setFixedSize(modifiedPixmap.size());
	// 设置按钮样式
	this->setStyleSheet("QPushButton{border:0px}");

	// 设置按钮图标
	this->setIcon(QIcon(modifiedPixmap));
	// 设置图标大小
	this->setIconSize(modifiedPixmap.size());

}

void Defense::setMargin(int left, int top, int right, int bottom)
{
    x_left_distance = left;
    y_top_distance = top;
    x_right_distancce = right;
    y_bottom_distance = bottom;
}

bool Defense::eventFilter(QObject* watched, QEvent* event)
{
    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
    switch (event->type())
    {
    case QEvent::MouseButtonPress:
    {
        if (mouseEvent->button() == Qt::LeftButton) {
            lastPoint = mouseEvent->pos();
            isPressed = true;
        }
        break;
    }
    case QEvent::MouseMove:
    {
        if (isPressed) {
            int dx = mouseEvent->pos().x() - lastPoint.x();
            int dy = mouseEvent->pos().y() - lastPoint.y();
            int x1 = this->x() + dx;
            int y1 = this->y() + dy;
            int right_distance = this->parentWidget()->width() - 2 * x_right_distancce - this->width();
            int bottom_distance = this->parentWidget()->height() - 2 * y_bottom_distance - this->height();
            if (x1 > x_left_distance && x1< right_distance && y1>y_top_distance && y1 < bottom_distance)
                this->move(this->x() + dx, this->y() + dy);
            isMoved = true;
        }
        break;
    }
    case QEvent::MouseButtonRelease:
    {
        qDebug() << "按钮被释放";
        qDebug() << isMoved;
        this->move(initPos.x(),initPos.y());
        if (isMoved != true) {

            emit clicked();
            emit toggled(!isChecked);
            isChecked = !isChecked;
        }
        else {
            isMoved = false;
        }
        isPressed = false;
        break;
    }
    case QEvent::MouseButtonDblClick:
        emit doubleClicked();
        break;
    default:
        break;
    }
    return QWidget::eventFilter(watched, event);
}
