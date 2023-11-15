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

	//this->bullet->move(initPos.x() + this->width() / 2 + 50, initPos.y() + 100)



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
            this->isShowing = true;
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
        double curx = cur.first;
        double cury = cur.second;
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
        QString towerPath = QString("./images/Fortress/%1_1.BMP").arg(this->defenseId);
        Defense* defense = new Defense(towerPath, pass1);



        shapeId = 1;

        //弹药
        for (int i = 0; i < 100; i++)
        {
            QString firePath = QString("./images/bullet%1.bmp").arg(this->defenseId);
            Bullet* bul = new Bullet(firePath,this);
            defense->bullets.push_back(bul);
        }

        //暂时用不到是想提前缓存动画省内存的发现好像没用.
        for (int i = 1; i <= 18; i++)
        {
            QString Tp = QString("./images/Fortress/%1_%2.BMP").arg(this->defenseId).arg(shapeId++);
			QPixmap originalPixmap;
			bool ret = originalPixmap.load(Tp);
			if (!ret)
				qDebug() << "failed";

			// 定义背景颜色的RGB值，例如绿色
			int red = 34;
			int green = 177;
			int blue = 76;

			// 创建一个副本，将背景颜色转换为透明
			QPixmap modifiedPixmap = originalPixmap;
			modifiedPixmap.setMask(originalPixmap.createMaskFromColor(QColor(red, green, blue)));

            defense->shapes.push_back(modifiedPixmap);
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

void Defense::attackAnimation(double x, double y)
{
    if (!attackEnd)
        return;
    attackEnd = false;
    QTimer* timer = new QTimer();
    timer->start(50);
    
    shapeId = 1;
    connect(timer, &QTimer::timeout, [=]() {

		if (shapeId > 18)
		{
            qDebug() << "size = " << this->bullets.size();
			this->bullet = bullets[bulletId++];
            
			this->bullet->move(initPos.x() + this->width() / 2 , initPos.y());
			//qDebug() << "bullet:" << bullet->pos();
			this->bullet->initX = initPos.x() + this->width() / 2;
			this->bullet->initY = initPos.y();
			this->bullet->show();
            this->bullet->raise();
			this->bullet->attack(x, y);
            shapeId = 1;
            attackEnd = true;
            timer->stop();
		}

        QString towerPath = QString("./images/Fortress/%1_%2.BMP").arg(this->defenseId).arg(shapeId++);
   //     qDebug() << "towerPath = " << towerPath;
    //    qDebug() << shapes.size();
        changeTower(towerPath);
      //  changeTower(this->shapes[shapeId - 1]);

    });

}

void Defense::attackAnimation(Enemy* enemy)
{
    if (!enemy->blood)
        return;
 //   qDebug() << "enemy->blood" << enemy->blood;
    if (!attackEnd)
        return;
    attackEnd = false;
 //   qDebug() << "enemy id = " << enemy->id;
    QTimer* timer = new QTimer();
    timer->start(50);

    shapeId = 1;
    connect(timer, &QTimer::timeout, [=]() {

        if (shapeId > 18)
        {
            //qDebug() << "size = " << this->bullets.size();
            this->bullet = bullets[bulletId++];

            this->bullet->move(initPos.x() + this->width() / 2, initPos.y());
            //qDebug() << "bullet:" << bullet->pos();
            this->bullet->initX = initPos.x() + this->width() / 2;
            this->bullet->initY = initPos.y();
            this->bullet->show();
            this->bullet->raise();
           // qDebug() << "enemy->id = " << enemy->id;
            this->bullet->attack(enemy);
            shapeId = 1;
            attackEnd = true;
            timer->stop();
        }

        QString towerPath = QString("./images/Fortress/%1_%2.BMP").arg(this->defenseId).arg(shapeId++);
        //     qDebug() << "towerPath = " << towerPath;
         //    qDebug() << shapes.size();
        changeTower(towerPath);
        //  changeTower(this->shapes[shapeId - 1]);

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

	this->setFixedSize(modifiedPixmap.size());
	// 设置按钮样式
	this->setStyleSheet("QPushButton{border:0px}");

	// 设置按钮图标
	this->setIcon(QIcon(modifiedPixmap));
	// 设置图标大小
	this->setIconSize(modifiedPixmap.size());

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

void Defense::sendDefenseID(int Id)
{
    emit Id;
}

QVector<bool> Defense::canMove;