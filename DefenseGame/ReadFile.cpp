#include "ReadFile.h"


ReadFile::ReadFile(QObject *parent)
	: QObject(parent)
{}

ReadFile::ReadFile()
{

}

void ReadFile::ReadPassInformation(QString path)
{

	// 创建一个文件对象
	QFile file(path);

	// 打开文件，以只读的方式
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "Could not open file for reading";
	}

	// 创建一个文本流对象，并将文件对象传递给它
	QTextStream in(&file);

	// 读取文件内容并输出到控制台
	passInformationId = 0;
	while (!in.atEnd())
	{
		QString line = in.readLine();

		if (passInformationId == 0)
		{
			mapPath = line;
		}

		if(passInformationId == 1)
		{
			enemyNum = line.toInt();
		}
		if (passInformationId == 2)
		{
			num = line.toInt();
		}
		if (passInformationId > 2 && passInformationId <= 2 + num)
		{
			QStringList point = line.split(" ");
			double p1 = point.at(0).toDouble();
			double p2 = point.at(1).toDouble();
			points.push_back(new QPoint(p1, p2));
		}
		if (passInformationId > 2 + num)
		{
			QStringList point = line.split(" ");
			double p1 = point.at(0).toDouble();
			double p2 = point.at(1).toDouble();
			pathPosition.push_back(new QPoint(p1, p2));
		}
		passInformationId++;

	}

	// 关闭文件
	file.close();


}

ReadFile::~ReadFile()
{}
