#pragma once

#include <QObject>

class QTimer  : public QObject
{
	Q_OBJECT

public:
	QTimer(QObject *parent);
	~QTimer();
};

