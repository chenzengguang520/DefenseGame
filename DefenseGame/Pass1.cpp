#include "Pass1.h"


Pass1::Pass1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);


	getInformation();

	isAttack.resize(num * 2 + 2);
	this->distances.resize(num * 2);
	for (int i = 0; i < num * 2; i++)
	{
		this->distances[i].resize(enemyNum + 2);
	}


	for (int i = 0; i < num * 2; i++)
	{
		for (int j = 0; j < enemyNum; j++)
		{
			this->distances[i][j] = MAX_NUM;
		}
	}

	this->installEventFilter(this);




	for (auto& cur : acPos)
	{
		DefenseTower* ac = new DefenseTower(this);
		double acx = cur.x();
		double acy = cur.y();
		//ac->move(acx, acy);
		ac->move(acx - ac->width() / 2,acy - ac->height() / 2);
// 		cur.setX(acx - ac->width() / 2);
// 		cur.setY(acy - ac->height() / 2);
		//ac->move(cur);
		ac->show();
	}



	//啥作用暂时忘了，不敢删
	Defense* defense11 = new Defense("./images/tower/tower1/tower1_0.png", this);
	defense11->setParent(this);
	defense11->show();


	Defense* defense12 = new Defense("./images/tower/tower2/tower2_0.png", this);
	defense12->setParent(this);
	defense12->move(defense11->size().width() + 5, 0);
	defense12->show();


	//左上角的两个防御塔
	QPoint q(0, 0);
	defense1 = new Defense(this,"./images/tower/tower1/tower1_0.png",q,num,1);

	defense1->setParent(this);
	defense1->show();

	
	Defense* defense2 = new Defense(this, "./images/tower/tower2/tower2_0.png", q, num,2);
	defense2->setParent(this);
	defense2->move(defense1->size().width() + 5,0);
	defense2->initPos = defense2->pos();
	defense2->show();

	

	int count = 0;
	for (auto& cur : acPos)
	{
		int posx = cur.x();
		int posy = cur.y();
		QPair<int, int>position(posx,posy);
		defense1->setPosition(position);
		defense2->setPosition(position);
		int towerWidth = defense1->towers[count]->width();
		int towerHeight = defense1->towers[count]->height();
		defense1->towers[count]->move(posx - towerWidth / 2, posy - towerHeight / 2);
		defense1->towers[count]->initPos = QPoint(posx - towerWidth / 2, posy - towerHeight / 2);
		defense1->towers[count]->setParent(this);
		defense1->towers[count]->hide();
		defense2->towers[count]->move(posx - towerWidth / 2, posy - towerWidth / 2);
		defense2->towers[count]->initPos = QPoint(posx - towerWidth / 2, posy - towerHeight / 2);
		defense2->towers[count]->setParent(this);
		defense2->towers[count++]->hide();

	}

	//设置弹药的爹
	for (auto& tower : defense1->towers)
	{
		for (auto& bullet : tower->bullets)
		{
			bullet->setParent(this);
			bullet->hide();
		}
	}

	for (auto& tower : defense2->towers)
	{
		for (auto& bullet : tower->bullets)
		{
			bullet->setParent(this);
			bullet->hide();
		}
	}

	//存储防御塔
	for (auto& defense : defense1->towers)
	{

		this->defenses.push_back(defense);
	}

	for (auto& defense : defense2->towers)
	{
		this->defenses.push_back(defense);
	}

	//gogogo
	//Enemy* enemy = new Enemy("./images/monster1/down_1.BMP");


	for (int i = 0; i < enemyNum; i++)
	{
		int _id = rand() % 3 + 1;
		QString eneP = QString("./images/monster%1/down_1.BMP").arg(_id);
		Enemy* enemy = new Enemy(eneP);

		if (_id == 1)
		{
			enemy->enemyMaxNum = 13;
		}

		if (_id == 2)
		{
			enemy->enemyMaxNum = 14;
		}
		if (_id == 3)
		{
			enemy->enemyMaxNum = 13;
		}

		enemy->initx = enemyPos[0].x() - enemy->width() / 2;
		enemy->inity = enemyPos[0].y() + 40 * i - enemy->height() / 2;
		enemy->destinationX = enemyPos[1].x() - enemy->width() / 2;
		enemy->destinationY = enemyPos[1].y() - enemy->height() / 2;
		enemy->dy = -1;
		enemy->id = _id;
		enemy->enemyPosId++;
		enemys.push_back(enemy);
	}
	
	for (int i = 0; i < enemyNum; i++)
	{
		enemyMove(enemys[i],i);
	}

}

Pass1::~Pass1()
{}


void Pass1::paintEvent(QPaintEvent* event)
{
//	getInformation();
	QPainter painter(this);
	QPixmap pixmap(mapPath);
	painter.drawPixmap(this->rect(), pixmap);
}

void Pass1::receiveId(int data)
{
	// 处理接收到的数据
	qDebug() << "Received data in pass1:" << data;
	defenseId = data;
}



void Pass1::paintTower(int id, int x, int y)
{

}

void Pass1::mousePressEvent(QMouseEvent* event)
{
	qDebug() << "event->pos() = " << event->pos();
}

void Pass1::updateDistance()
{
//	qDebug() << "update function is runing";
	for (int i = 0; i < num * 2; i++)
	{
		for (int j = 0; j < enemyNum; j++)
		{
			//qDebug() << "i = " << i << " j = " << j << " isShow = " << defenses[i]->isShowing << " &this = " << &distances[i];
			distances[i][j] = MAX_NUM;
			if (!defenses[i]->isVisible())
			{
				
				break;
			}
			double x1 = this->defenses[i]->pos().x();
			double y1 = this->defenses[i]->pos().y();
			double x2 = this->enemys[j]->initx;
			double y2 = this->enemys[j]->inity;
			double dis = getDistance(x1, y1, x2, y2);
			//qDebug() << "dis = " << dis;
			this->distances[i][j] = dis;
		}
	}

}

void Pass1::getInformation()
{
	ReadFile* readFile = new ReadFile();
	readFile->ReadPassInformation("./file/Game Level/pass1.txt");
	mapPath = readFile->mapPath;
	qDebug() << "map path = " << mapPath;
	enemyNum = readFile->enemyNum;
	num = readFile->num;


	QPoint p1(266, 117);
	QPoint p2(414, 272);


	for (const auto& point : readFile->points)
	{
		acPos.push_back(*point);
	}
	this->resize(1024, 568);


	for (const auto& point : readFile->pathPosition)
	{
		enemyPos.push_back(*point);
	}



}

QPair<double,double> Pass1::getGap(double x, double y,double V)
{
// 	if (x == 0)
// 	{
// 		return QPair<double, double>(0, 1.0);
// 	}
	double arctan_value = atan(y * V / x);
	//double tana = y * V / x;
	double tana = tan(arctan_value);
	tana = tana > 0 ? tana : -1 * tana;
// 	double vx = 1.0 / sqrt(1 + tana);
// 	double vy = 1.0 / sqrt(1 + tana) * tana;

	double vx = 1 * cos(arctan_value);
	double vy = 1 * sin(arctan_value);

	if (x > 0)
	{
		vx = vx > 0 ? vx : -1 * vx;
	}
	else
	{
		vx = vx < 0 ? vx : -1 * vx;
	}
	if (y > 0)
	{
		vy = vy > 0 ? vy : -1 * vy;
	}
	else
	{
		vy = vy < 0 ? vy : -1 * vy;
	}
	return QPair<double, double>(vx, vy);
}

void Pass1::enemyMove(Enemy* enemy,int index)
{

	QTimer* timer = new QTimer;

	timer->start(50);
	enemy->setParent(this);
	enemy->show();

	connect(timer, &QTimer::timeout, [=]() {

		if (isEnd)
			return;

		//enemy->move(450.0 + enemy->width() / 2, 0 + enemy->height() / 2);
	
		if (!enemy->isChange)
			enemy->enemyPath = QString(QString("./images/monster%1/down_%2.BMP").arg(enemy->id).arg(enemy->enemyMinNum++));
		else
			enemy->enemyPath = QString(QString("./images/monster%1/Right_%2.BMP").arg(enemy->id).arg(enemy->enemyMinNum++));
		enemy->changShape(enemy->enemyPath);
		double X = enemy->destinationX - enemy->initx;
		double Y = enemy->destinationY - enemy->inity;
		QPair<double, double> v = getGap(X, Y, 1.0);
		enemy->dx = v.first;
		enemy->dy = v.second; 
		enemy->initx += enemy->dx;
		enemy->inity += enemy->dy;
		enemy->move(enemy->initx, enemy->inity);

		//判断是否可攻击
		updateDistance();
		for (int i = 0; i < num * 2; i++)
		{
		//	qDebug() << "attackRadius" << defenses[i]->attackRadius;
			//qDebug()<<"dis = "<< distances[i][index] << "attackRadius" << defenses[i]->attackRadius;
			if (distances[i][index] <= defenses[i]->attackRadius)
			{

				/*怪物倒地之后还会多攻击一次因为上一次攻击还没结束，怪物还没死亡*/
				this->defenses[i]->attackAnimation(enemy);
				if (enemy->blood <= 0)
				{
					enemy->hide();
					timer->stop();
					return;
				}
			}
		}


		if (enemy->inity - enemy->destinationY <= 2 && enemy->inity - enemy->destinationY >= -2 && enemy->initx - enemy->destinationX <= 2 && enemy->initx - enemy->destinationX >= -2)
		{
			enemy->initx = enemy->destinationX;
			enemy->inity = enemy->destinationY;
			if (enemy->initx == this->width())
			{

				SettlementScreen* screen = new SettlementScreen();
				screen->setParent(this);
				screen->show();
				screen->move(0, 0);
				isEnd = true;
				timer->stop();
				return;
			}

			if (enemy->inity == 350.0)
			{
				enemy->isChange = true;

				if (enemy->id == 1)
				{
					enemy->enemyMaxNum = 17;
				}

				if (enemy->id == 2)
				{
					enemy->enemyMaxNum = 14;
				}
				if (enemy->id == 3)
				{
					enemy->enemyMaxNum = 13;
				}

			}
			enemy->destinationX = enemyPos[++enemy->enemyPosId].x() - enemy->width() / 2;
			enemy->destinationY = enemyPos[enemy->enemyPosId].y() - enemy->height() / 2;
			X = enemy->destinationX - enemy->initx;
			Y = enemy->destinationY - enemy->inity;
			v = getGap(X, Y, 1.0);
			enemy->dx = v.first;
			enemy->dy = v.second;
		}
		if (enemy->enemyMinNum + 1 > enemy->enemyMaxNum)
		{
			enemy->enemyMinNum = 1;
		}
		
	});

}

double Pass1::getDistance(double x1, double y1, double x2, double y2)
{
	double ans = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	return ans;
}
