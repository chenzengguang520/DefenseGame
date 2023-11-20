#pragma once

#include <QObject>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QPoint>

class ReadFile  : public QObject
{
	Q_OBJECT

public:
	ReadFile(QObject *parent);
	ReadFile();
	void ReadPassInformation(QString path);
	~ReadFile();

public:
	int enemyNum = 0;
	int num = 0;
	QVector<QPoint*>points;
	QVector<QPoint*>pathPosition;
	int passInformationId = 0;
	QString mapPath = "";
};
