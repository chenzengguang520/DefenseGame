#pragma once

#include <QtWidgets/QWidget>
#include "ui_DefenseGame.h"
#include <QPainter.h>
#include <QDebug>
#include <QPushButton>
#include "Pass1.h"


class DefenseGame : public QWidget
{
    Q_OBJECT

public:
    DefenseGame(QWidget *parent = nullptr);
    ~DefenseGame();
    void paintEvent(QPaintEvent* ev);

private:
    Ui::DefenseGameClass ui;
};
