#include "Enemy.h"



Enemy::Enemy(QObject *parent)
	: QObject(parent)
{}

Enemy::~Enemy()
{}

Enemy::Enemy()
{
}

Enemy::Enemy(int b, int s, int d)
{
	this->blood = b;
	this->speed = s;
	this->id = d;
}

void Enemy::move(int x, int y, int endX, int endY)
{
	QLabel* enemy = new QLabel();
	
}
