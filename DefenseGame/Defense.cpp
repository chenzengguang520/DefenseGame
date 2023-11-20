#include "Defense.h"


// Defense::Defense(QObject *parent)
// 	: QObject(parent)
// {}

Defense::Defense()
{
}

Defense::~Defense()
{}

Defense::Defense(QWidget* _pass1,QString path, QPoint q,int num,int id)
{



	this->path = path;

    this->defenseId = id;

    canMove.resize(num + 5);

    makeDefenses(num);

    this->pass1 = _pass1;
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

Defense::Defense(QString path, QWidget* parent)
{
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


			// 获取鼠标相对于小部件的位置
			QPoint localPos = mouseEvent->pos();

			// 将相对于小部件的坐标映射到父级窗口的坐标系
			QPoint parentPos = mapToParent(localPos);

			// 在MouseMove事件中，您可能需要使用之前记录的lastPoint作为起点进行坐标变化的计算
			int dx1 = localPos.x() - lastPoint.x();
			int dy1 = localPos.y() - lastPoint.y();
			int x11 = this->x() + dx1;
			int y11 = this->y() + dy1;

          //  qDebug() << "mouseEventx = " << x11 << " " << "mouseEventy = " << y11;
            int dx = mouseEvent->pos().x() - lastPoint.x();
            int dy = mouseEvent->pos().y() - lastPoint.y();
            int x1 = this->x() + dx;
            int y1 = this->y() + dy;
            int right_distance = this->parentWidget()->width() - 2 * x_right_distancce - this->width();
            int bottom_distance = this->parentWidget()->height() - 2 * y_bottom_distance - this->height();
            if (x1 > x_left_distance && x1< right_distance && y1>y_top_distance && y1 < bottom_distance)
                this->move(this->x() + dx, this->y() + dy);
            isMoved = true;
      
            int ret = check(event);
            if (!canMove[ret + 1])
            {
				if (ret != -1 && isCheckAc)
				{
					qDebug() << " ret = " << ret;

					for (const auto& cur : positon)
					{
						qDebug() << "cur.x = " << cur.first << " cur.y = " << cur.second;
					}

					des = towers[ret];
					des->show();
					isShow = true;
					isCheckAc = false;
				}
				if (ret == -1 && isShow)
				{
					isShow = false;
					des->hide();
				}
            }
         
        }
        break;
    }
    case QEvent::MouseButtonRelease:
    {
      //  qDebug() << "按钮被释放";
     //   qDebug() << isMoved;


        if (isMoved != true) {

            emit clicked();
            emit toggled(!isChecked);
            isChecked = !isChecked;
        }
        else {
            isMoved = false;
        }
        isPressed = false;
        if (isShow)
        {
            des->hide();
            isShow = false;
        }
        int ret = check(event);
        if (ret != -1 && !canMove[ret + 1])
        {
            canMove[ret + 1] = 1;
            this->towers[ret]->show();
            this->towers[ret]->isShowing = true;
        }
        this->move(initPos.x(),initPos.y());
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

void Defense::setPosition(QPair<double, double> p)
{
    this->positon.push_back(p);
}

int Defense::check(QEvent* event)
{
   // qDebug() << "checking";
    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
	// 获取鼠标相对于小部件的位置
	QPoint localPos = mouseEvent->pos();

	// 将相对于小部件的坐标映射到父级窗口的坐标系
	QPoint parentPos = mapToParent(localPos);
	int dx1 = localPos.x() - lastPoint.x();
	int dy1 = localPos.y() - lastPoint.y();
	int x = this->x() + dx1;
	int y = this->y() + dy1;
    QPair<double, double>q(x, y);
    int count = 0;
    for (const auto& cur : positon)
    {
        double curx = cur.first - this->width() / 2;
        double cury = cur.second - this->height() / 2;
        if (x > curx - 10 && x < curx + 10 && y > cury - 10 && y < cury + 10)
        {
            isCheckAc = true;
            return count;
        }
        count++;
    }
    isCheckAc = true;
    return -1;
}


void Defense::makeDefenses(int num)
{
    for (int i = 0; i < num; i++)
    {
        QString towerPath = QString("./images/tower/tower%1/tower%2_0").arg(this->defenseId).arg(this->defenseId);
        qDebug() << "towerPath = " << towerPath;
        Defense* defense = new Defense(towerPath, pass1);



        shapeId = 1;

        //弹药
        for (int i = 0; i < 200; i++)
        {
            QString firePath = QString("./images/bullet/bullet1.png").arg(this->defenseId);
           
            Bullet* bul = new Bullet(firePath,this);
            defense->bullets.push_back(bul);
        }


        defense->defenseId = defenseId;
        defense->isShowing = false;
        defense->attackRadius = 200;
        towers.push_back(defense);
    }
}

bool Defense::isShowed()
{
    return this->isShowing;
}

void Defense::attackAnimation(Enemy* enemy)
{
    if (!this->isShowing)
        return;
    if (!enemy->blood)

        return;
    if (!attackEnd)
        return;
    attackEnd = false;
    QTimer* timer = new QTimer();
    timer->start(10);

    shapeId = 1;
    
    x0 = this->pos().x() + 0.5 * this->width();
    y0 = this->pos().y() + 0.5 * this->height();
    


    connect(timer, &QTimer::timeout, [=]() {
        
        if (canTransform)
        {
            x1 = enemy->pos().x() + 0.5 * enemy->width();
            y1 = enemy->pos().y() + 0.5 * enemy->height();

            angleC = getAngle(x0, y0, x1, y1, x0, this->pos().y());

            angleC = x1 < x0 ? -1 * angleC : angleC;

            angleB = angleC - angleA;

            dAngle = angleB < 0 ? -1 : 1;

            canTransform = false;

        }
		angleB = angleC - angleA;

		dAngle = angleB < 0 ? -1 : 1;
        auto abs = [=](int num) -> int {
            return num < 0 ? -1 * num : num;
        };



        bool ret = angleA == angleC;
        if (ret)
        {
            double angleA_ = (angleA / 180.0) * PI;
            x2 = x0 + 0.5 * this->height() * sin(angleA_);
            y2 = y0 - 0.5 * this->height() * cos(angleA_);
		 
            if (shapeId > 5)
            {
                qDebug() << " id = " << enemy->id;
				this->bullet = bullets[bulletId++];
                this->bullet->destinationX = x1;
                this->bullet->destinationY = y1;
				this->bullet->move(x2 - this->bullet->width() * 0.5, y2 - this->bullet->height() * 0.5);
				this->bullet->initX = x2 - this->bullet->width() * 0.5;
				this->bullet->initY = y2 - this->bullet->height() * 0.5;
				this->bullet->show();
				this->bullet->attackEnd = false;
				this->bullet->attack(enemy);
                shapeId = 1;
            }

            canTransform = true;

            if (!enemyCheck(enemy))
            {
				attackEnd = true;
				timer->stop();
            }

            
        }
        if (changeEnd && !canTransform)
        {
            shapeId++;
			changeEnd = false;
			changeTower(dAngle + angleA);
			changeEnd = true;
        }

    });


}

void Defense::changeTower(QString towerPath)
{

	QPixmap originalPixmap;
	bool ret = originalPixmap.load(towerPath);
	if (!ret)
		qDebug() << "failed";

	// 定义背景颜色的RGB值，例如绿色
	int red = 34;
	int green = 177;
	int blue = 76;

    // 创建一个副本，将背景颜色转换为透明
    QPixmap modifiedPixmap = originalPixmap;
    modifiedPixmap.setMask(originalPixmap.createMaskFromColor(QColor(red, green, blue)));

    // 设置旋转角度
    int rotationAngle = 0; // 替换为你需要的旋转角度
    QTransform transform;
    //transform.rotate(rotationAngle);
    modifiedPixmap = modifiedPixmap.transformed(transform, Qt::SmoothTransformation);

    // 设置按钮大小
    this->setFixedSize(modifiedPixmap.size());

    // 设置按钮样式
    this->setStyleSheet("QPushButton{border:0px}");

    // 设置按钮图标
    this->setIcon(QIcon(modifiedPixmap));

    // 设置图标大小
    this->setIconSize(modifiedPixmap.size());
   

}


void Defense::changeTower(int _angle)
{
	QPixmap originalPixmap;
    path = QString("./images/tower/tower%1/tower%2_%3.png").arg(this->defenseId).arg(this->defenseId).arg(_angle);
	bool ret = originalPixmap.load(this->path);
	if (!ret)
		qDebug() << "failed";

	// 定义背景颜色的RGB值，例如绿色
	int red = 34;
	int green = 177;
	int blue = 76;

	// 创建一个副本，将背景颜色转换为透明
	QPixmap modifiedPixmap = originalPixmap;
	modifiedPixmap.setMask(originalPixmap.createMaskFromColor(QColor(red, green, blue)));


	// 设置按钮大小
	this->setFixedSize(modifiedPixmap.size());

	// 设置按钮样式
	this->setStyleSheet("QPushButton{border:0px}");

	// 设置按钮图标
	this->setIcon(QIcon(modifiedPixmap));

	// 设置图标大小
	this->setIconSize(modifiedPixmap.size());
    angleA += dAngle;
}


void Defense::changeTower(QPixmap& modifiedPixmap)
{

	this->setFixedSize(modifiedPixmap.size());
	// 设置按钮样式
	this->setStyleSheet("QPushButton{border:0px}");

	// 设置按钮图标
	this->setIcon(QIcon(modifiedPixmap));
	// 设置图标大小
	this->setIconSize(modifiedPixmap.size());

}

void Defense::opebFire(double x, double y)
{

}

//可以继续攻击这个怪返回true
bool Defense::enemyCheck(Enemy* enemy)
{
    double x = enemy->initx;
    double y = enemy->inity;
    double dist = sqrt((this->pos().x() - x) * (this->pos().x() - x) + (this->pos().y() - y) * (this->pos().y() - y));
    if (dist > attackRadius || enemy->blood <= 0)
        return false;
    return true;
}

void Defense::spin(double angle)
{



}

double Defense::getAngle(double x0, double y0, double x1, double y1,double x2,double y2)
{
    double C = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    double A = sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
    double B = sqrt((x2 - x0) * (x2 - x0) + (y2 - y0) * (y2 - y0));
    double cosAngle = (A * A + B * B - C * C) * 1.0 / (2 * A * B);
    double agl = acos(cosAngle);



    return agl * 180 / PI;

}


void Defense::sendDefenseID(int Id)
{
    emit Id;
}

QVector<bool> Defense::canMove;