#pragma once

#include <QtWidgets/QWidget>
#include "ui_DefenseGame.h"

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
